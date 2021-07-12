#pragma once
#include "pch.h"

using namespace std;
namespace fs = std::filesystem;

// Handles the app parameters
class Parameters {
 private:
    fs::path root{fs::current_path()};

 public:
    enum class ParamsType { DefaultParams, ThresholdOnly, FullParams, HelpCommand, Unknown};

    fs::path reference_folder{root / "input" / "references"};
    fs::path images_folder{root / "input" / "images"};
    fs::path masks_folder{root / "input" / "masks"};
    fs::path diff_folder{root / "output" / "diff"};
    fs::path reports_folder{root / "output" };
    int threshold{0};
    
    bool show_images_while_processing{true};

    const std::string default_mask_name{"_mask.png"};

    ParamsType load_from_args(int argc, char** argv);

    std::string to_string() const;
    void print() const;
    ParamsType type() const;
    static void print_syntax();
    static void print_examples();

 private:
    ParamsType _type{ParamsType::Unknown};
    bool is_help_command(std::string command) const;
    unsigned char decode_threshold(const string argument) const;
    std::filesystem::path generate_diff_path(const string path) const;
};