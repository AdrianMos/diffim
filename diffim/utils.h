#pragma once
#include "utils.h"
#include "Parameters.h"

void print_app_title();
void print_separator();
void print_separator(size_t length, char filler);
void print_centered(std::string title, size_t width, char filler_char = ' ');

void check_input_folders_existance(const Parameters& p);
void create_output_folders(const Parameters& p);
void create_input_folders(const Parameters& p);
