#include "utils.h"


void print_app_title()
{
    size_t width = 60;
    print_separator(width, '*');
    print_centered("diffim", width, ' ');
    print_separator(width, ' ');
    print_centered("image comparing tool with masks support", width, ' ');
    print_centered("V 1.0, 07.2020", width, ' ');
    print_separator(width, '*');
    std::cout << "\n";
}

void print_centered(std::string title, size_t width, char filler_char)
{
    size_t length = title.size();
    if (width < length)
        width = length;

    size_t filler_size = (width - length) / 2;
    std::string filler(filler_size, filler_char);

    std::cout << filler << " " << title << " " << filler << "\n";
}


void print_separator(size_t length, char filler)
{
    std::cout << std::string(length, filler) << "\n";
}

void print_separator()
{
    print_separator(60, '*');
}


void check_input_folders_existance(const Parameters& p)
{
    if (!fs::exists(p.reference_folder)) {
        throw std::invalid_argument("The reference folder does not exist!");
    }

    if (!fs::exists(p.images_folder)) {
        throw std::invalid_argument("The images folder does not exist!");
    }
}


void create_output_folders(const Parameters& p)
{
    if (fs::exists(p.diff_folder)) {
        fs::remove_all(p.diff_folder);
    }

    if (!fs::create_directories(p.diff_folder))
        throw std::exception("Failed to create output folder!");
}


void create_input_folders(const Parameters& p)
{
    try {
        fs::create_directories(p.reference_folder);
        fs::create_directories(p.images_folder);
        fs::create_directories(p.masks_folder);
    }
    catch (...) {
        throw std::exception("Failed to create default folders.");
    }
}
