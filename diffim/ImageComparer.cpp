#include "pch.h"

#include "ComparableEntity.h"
#include "ImageComparer.h"


ImageComparer::ImageComparer(bool show_images_while_processing = false)
    : show_images_while_processing(show_images_while_processing)
{
}


void ImageComparer::compare_all(std::vector<ComparableEntity>& items)
{
    std::cout << "Starting image comparison:\n";

    if (show_images_while_processing)
        initialize_display_windows();

    for (auto& item : items) {
        compare(item);

        if (show_images_while_processing)
            update_display_windows();
    }
}

void ImageComparer::compare(ComparableEntity& comparison)
{
    comparison.status = compare_image(comparison.reference, comparison.image,
                                      comparison.mask, comparison.threshold);

    if (comparison.status == ComparisonStatus::Different) {
        fs::create_directories(comparison.diff.parent_path());
        cv::imwrite(comparison.diff.string(), _difference);
    }

    std::cout << "  " << convert_status_to_string(comparison.status) << "  "
              << comparison.relative_path.string() << '\n';
}


cv::Mat ImageComparer::load_or_create_mask(const fs::path path,
                                           const cv::Size expected_size)
{
    cv::Mat mask = load_mask(path);

    bool empty_or_wrong_size = mask.empty() || mask.size() != expected_size;

    if (empty_or_wrong_size)
        return create_mask(expected_size);

    return mask;  // this return is efficient; cv::Mat uses smart pointers
                  // internally
}


cv::Mat ImageComparer::load_mask(const fs::path path)
{
    cv::Mat mask;
    cv::Mat img = cv::imread(path.string(), IMREAD_GRAYSCALE);
    cv::threshold(img, mask, 100, 255, THRESH_BINARY);
    return mask;
}

cv::Mat ImageComparer::create_mask(cv::Size size)
{
    return cv::Mat::ones(size, CV_8U);
}


ComparisonStatus ImageComparer::compare_image(fs::path reference_image_path,
                                              fs::path image_path,
                                              fs::path mask_path,
                                              int threshold = 0)
{
    auto status{ComparisonStatus::NotCompared};

    _image = Scalar(0, 0, 0);
    _difference = Scalar(0, 0, 0);
    _reference = Scalar(0, 0, 0);

    _reference = cv::imread(reference_image_path.string(), IMREAD_COLOR);
    if (_reference.empty())
        return ComparisonStatus::NotCompared;

    _image = cv::imread(image_path.string(), IMREAD_COLOR);
    if (_image.empty())
        return ComparisonStatus::ImageMissing;

    if (_reference.size() != _image.size())
        return ComparisonStatus::Different;

    // Compute the diff & set all different pixels to red
    cv::absdiff(_reference, _image, _difference);
    _difference.forEach<Pixel>(ColorizePixelMismatchFunctor(threshold));

    _difference = extract_differences_inside_masked_region(mask_path);

    // red channel stores the differences
    auto diferent_pixels_count
        = count_non_zero_pixels(_difference, Channel::red);

    if (diferent_pixels_count > 0)
        return ComparisonStatus::Different;
    else
        return ComparisonStatus::Identical;
}

cv::Mat ImageComparer::extract_differences_inside_masked_region(
    const fs::path mask_path)
{
    cv::Mat masked_differences;
    auto mask = load_or_create_mask(mask_path, _reference.size());
    _difference.copyTo(masked_differences, mask);
    return masked_differences;  // safe; cv::Mat uses smart pointers internally
}


int ImageComparer::count_non_zero_pixels(const cv::Mat& diff,
                                         const Channel channel)
{
    cv::Mat bgr[3];
    split(diff, bgr);
    return cv::countNonZero(bgr[static_cast<int>(channel)]);
}

void ImageComparer::initialize_display_windows()
{
    namedWindow("Image");
    moveWindow("Image", 100, 20);

    namedWindow("Reference");
    moveWindow("Reference", 700, 20);

    namedWindow("diff");
    moveWindow("diff", 400, 20);

}

void ImageComparer::update_display_windows()
{
    if (!_image.empty())
        imshow("Image", _image);

    if (!_reference.empty())
        imshow("Reference", _reference);

    if (!_difference.empty())
        imshow("diff", _difference);
    waitKey(1);
}
