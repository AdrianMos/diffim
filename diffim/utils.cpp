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


void print_app_ending()
{
    print_separator();
}




