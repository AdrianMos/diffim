#pragma once
#include <string>
#include <iostream>

void print_app_title();
void print_app_ending();

void print_separator(size_t length = 60, char filler ='*');
void print_centered(std::string title, size_t width, char filler_char = ' ');
