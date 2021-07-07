#pragma once
#include "pch.h"

#include "ColorizePixelMismatchFunctor.h"
#include "ComparableEntity.h"
#include "Parameters.h"

using namespace cv;

// The actual image comparison happens here (based on OpenCV)
class ImageComparer {
 public:
    ImageComparer(bool show_images_while_processing);
    void compare_all(std::vector<ComparableEntity>& items);
    void compare(ComparableEntity& comparison);

 private:
    bool show_images_while_processing{true};

    ComparisonStatus compare_image(const fs::path reference_image_path,
                                   const fs::path image_path,
                                   const fs::path mask_path,
                                   const int threshold);

    cv::Mat _reference;
    cv::Mat _image;
    cv::Mat _difference;

    cv::Mat load_or_create_mask(const fs::path path,
                                const cv::Size expected_size);
    cv::Mat load_mask(const fs::path path);
    cv::Mat create_mask(const cv::Size size);

    cv::Mat extract_differences_inside_masked_region(const fs::path mask_path);

    void initialize_display_windows();
    void update_display_windows();

    enum class Channel { blue, green, red };
    int count_non_zero_pixels(const cv::Mat& diff, const Channel channel);
};