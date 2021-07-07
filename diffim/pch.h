#ifndef PCH_H
#define PCH_H

// TODO: add headers that you want to pre-compile here
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"

#include <Windows.h>
#include <stdio.h>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>

typedef cv::Point3_<uint8_t> Pixel;

enum class ComparisonStatus { NotCompared = 0, Identical, Different, ImageMissing };
std::string convert_status_to_string(ComparisonStatus status);

#endif //PCH_H
