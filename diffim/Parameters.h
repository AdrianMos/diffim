#pragma once
#include "pch.h"

using namespace std;
namespace fs = std::filesystem;

// Handles the app parameters
class Parameters {
 private:
    fs::path root{fs::current_path()};

 public:
    enum class ParamsType { DefaultParams, ThresholdOnly, FullParams };

    fs::path reference_folder{root / "references"};
    fs::path compare_folder{root / "images"};
    fs::path masks_folder{root / "masks"};
    fs::path diff_folder{root / "diff"};
    fs::path reports_folder{root};
    int threshold{0};
    ParamsType type{ParamsType::DefaultParams};
    bool show_images_while_processing{true};

    const std::string default_mask_name{"_mask.png"};

    const std::string to_string();
    const void print();
    void load_from_args(int argc, char** argv);

    static void print_cmd_syntax();

 private:
    unsigned char decode_threshold(const string argument);
    std::filesystem::path generate_diff_path(const string path);
};