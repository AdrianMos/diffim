// pch.cpp: source file corresponding to pre-compiled header; necessary for compilation to succeed
#include "pch.h"


std::string convert_status_to_string(ComparisonStatus status)
{
    switch (status) {
        case ComparisonStatus::Identical: return "OK";
        case ComparisonStatus::Different: return "NOK";
        case ComparisonStatus::NotCompared: return "NotCompared";
        case ComparisonStatus::ImageMissing: return "ImageMissing";
        default: return "NOK";
    }
}
