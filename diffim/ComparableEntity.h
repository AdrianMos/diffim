#pragma once
#include "pch.h"

using namespace std;
namespace fs = std::filesystem;

class ComparableEntity {
 public:
    ComparisonStatus status{ComparisonStatus::NotCompared};

    ComparableEntity(const fs::path& reference,
                     const fs::path& image,
                     const fs::path& diff,
                     const fs::path& mask,
                     const fs::path& relative_path,
                     const unsigned char threshold);

    fs::path reference{""};
    fs::path image{""};
    fs::path diff{""};
    fs::path mask{""};
    unsigned char threshold{0};

    // image path relative to the reference base folder
    fs::path relative_path{""};  // e.g.fpke\dev\lists\infoprofile0_no_move.png
};
