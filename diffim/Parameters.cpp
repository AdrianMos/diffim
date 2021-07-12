#include "Parameters.h"
#include "pch.h"


std::string Parameters::to_string() const
{
    return (std::string) "Parameters:\n" + " INPUT:\n"
           + "  images:           " + images_folder.string() + "\n"
           + "  references:       " + reference_folder.string() + "\n"
           + "  masks:            " + masks_folder.string() + "\n"
           + "  threshold:        " + std::to_string(threshold) + "\n" + "\n"
           + " OUTPUT:\n"  //
           + "  diff images:      " + diff_folder.string() + "\n"
           + "  reports:          " + reports_folder.string()
           + "\\ (.json, .csv)\n\n";
}

void Parameters::print() const
{
    std::cout << to_string();
}

bool Parameters::is_help_command(std::string command) const
{
    return (command == "-help") || (command == "--help") || (command == "-h")
           || (command == "--help");
}

Parameters::ParamsType Parameters::type() const
{
    return _type;
}

Parameters::ParamsType Parameters::load_from_args(int argc, char** argv)
{
    switch (argc) {
        case 1: _type = ParamsType::DefaultParams; break;

        case 2:
            if (is_help_command(argv[1])) {
                _type = ParamsType::HelpCommand;
            }
            else {
                _type = ParamsType::ThresholdOnly;
                threshold = decode_threshold(string(argv[1]));
            }
            break;
        case 7:
            _type = ParamsType::FullParams;
            reference_folder = argv[1];
            images_folder = argv[2];
            masks_folder = argv[3];
            threshold = decode_threshold(string(argv[4]));
            diff_folder = generate_diff_path(string(argv[5]));
            reports_folder = argv[6];
            break;
        default: _type = ParamsType::Unknown; break;
    }

    return _type;
}

std::filesystem::path Parameters::generate_diff_path(const string path) const
{
    return path + "\\differences";
}

unsigned char Parameters::decode_threshold(const string argument) const
{
    int value{0};
    try {
        value = std::stoi(argument);
    }
    catch (std::exception ex) {
        throw std::invalid_argument("Invalid threshold: \"" + argument + "\"");
    }

    if (value < 0 || value > 255)
        throw std::invalid_argument("Threshold " + std::to_string(value)
                                    + " out of accepted range [0,255].");

    return static_cast<unsigned char>(value);
}


void Parameters::print_syntax()
{
    std::cout << "Valid syntax: \n";
    std::cout << std::string(50, '-') << "\n\n";
    std::cout << "1. diffim.exe\n"
                 "2. diffim.exe -help\n"
                 "3. diffim.exe threshold[0..255]\n"
                 "4. diffim.exe \"reference_folder\" \"images_folder\" "
                 "\"masks_folder\" \"threshold\" \"OUT_diff_folder\" "
                 "\"OUT_report_folder\"  \n\n";
    // std::cout << std::string(60, '*') << "\n";
}


void Parameters::print_examples()
{
    std::cout << "\nExamples: \n";
    std::cout << std::string(50, '-') << "\n";
    std::cout
        << "\n1) diffim.exe\n"
           "    Default parameters and local folders are used. \n"
           "    The input-output folders are automatically created.\n"
           "     INPUT:\n"
           "       reference folder:        .\\input\\references\\\n"
           "       compared images folder:  .\\input\\images\\\n"
           "       masks folder:            .\\input\\masks\\\n"
           "       threshold:               0\n"
           "     OUTPUT:\n"
           "       differences folder:      .\\output\\differences\\\n"
           "       reports:                 .\\output\\comparison.json and "
           "comparison.csv\n"

           "\n2) diffim.exe 100\n"
           "    Comparison threshold set to 100; default local paths are "
           "used.\n"

           "\n3) diffim.exe \"C:\\\\ref\" \"C:\\\\images\" \"C:\\\\masks\" "
           "\"10\" \"C:\\\\out\\\\diff\" \"C:\\\\out\\\\reports\"\n"
           "    Custom paths; threshold is set to 10.\n";

    std::cout << "\n\n";
}