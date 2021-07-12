#include "FolderScanner.h"

FolderScanner::FolderScanner(const Parameters& params) : _params(params)
{
}

std::vector<ComparableEntity> FolderScanner::scan()
{
    std::vector<ComparableEntity> comparable_items;

    for (const auto& reference_file :
         std::filesystem::recursive_directory_iterator(
             _params.reference_folder)) {
        bool is_comparable = !fs::is_directory(reference_file)
                             && is_supported_format(reference_file.path());

        if (is_comparable) {
            auto relative_path
                = fs::relative(reference_file, _params.reference_folder);

            comparable_items.push_back(
                ComparableEntity(reference_file,
                                 _params.images_folder / relative_path,
                                 _params.diff_folder / relative_path,
                                 find_mask(reference_file),
                                 relative_path,
                                 _params.threshold));
        }
    }

    return comparable_items;
}


bool FolderScanner::is_supported_format(const fs::path& file)
{
    string ext = file.extension().string();
    if (ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".bmp")
        return true;
    return false;
}


std::string FolderScanner::find_mask(const fs::path& reference_image) const
{
    auto relative_name = fs::relative(reference_image, _params.reference_folder);
    fs::path mask = _params.masks_folder / relative_name;
    if (!fs::exists(mask)) {
        mask = _params.masks_folder / relative_name.parent_path()
               / _params.default_mask_name;
        if (!fs::exists(mask))
            mask = "";
    }

    return mask.string();
}
