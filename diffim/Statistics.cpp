#include "Statistics.h"
#include "pch.h"

void Statistics::add_status(ComparisonStatus status)
{
    switch (status) {
        case ComparisonStatus::Identical: _identical++; break;
        case ComparisonStatus::Different: _different++; break;
        case ComparisonStatus::NotCompared: _not_compared++; break;
        case ComparisonStatus::ImageMissing: _missing++; break;
        default: throw std::invalid_argument("Unknown status"); break;
    }
}

string Statistics::to_string()
{
    return   " total comparisons: " + std::to_string(total()) + "\n"
           + "  identical:    " + std::to_string(identical()) + "\n"
           + "  different:    " + std::to_string(different()) + "\n"
           + "  missing:      " + std::to_string(missing()) + "\n"
           + "  not compared: " + std::to_string(not_compared());
}

int Statistics::total()
{
    return identical() + different() + missing() + not_compared();
}

void Statistics::print()
{
    std::cout << "\nStatistics: \n" << to_string() << "\n";
}