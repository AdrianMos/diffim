#pragma once
#include "pch.h"

#include "ComparableEntity.h"
#include "Parameters.h"

// Finds and groups comparable items (reference images, images and masks) in a
// vector, which is later used for the actual image comparison.
class FolderScanner {
 public:
    FolderScanner(const Parameters& params);
    std::vector<ComparableEntity> scan();

 private:
    Parameters _params;

    // Mask search algorithm:
    //   1. First, a mask having an identical name is searched in the masks
    //   folder.
    //   2. In case of failure, a folder specific mask is searched (_mask.png).
    //   3. In case of failure, an empty string is returned.
    std::string find_mask(const fs::path& reference_image);

    bool is_supported_format(const fs::path& file);
};