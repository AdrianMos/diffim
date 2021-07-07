#include "pch.h"
#include "Parameters.h"


const std::string Parameters::to_string()
{
    return (std::string) "Parameters:\n" 
           + " INPUT:\n"   
           + "  images:           " + compare_folder.string() + "\n"
           + "  references:       " + reference_folder.string() + "\n"
           + "  masks:            " + masks_folder.string() + "\n"
           + "  threshold:        " + std::to_string(threshold) + "\n"
           + "\n" 
           + " OUTPUT:\n"
           + "  diff images:  " + diff_folder.string() + "\n"
           + "  reports:      " + reports_folder.string() + "\\ (.json, .tsv)\n\n";
}

const void Parameters::print()
{
    std::cout << to_string();
}

void Parameters::load_from_args(int argc, char** argv)
{
    bool is_num_params_valid = argc == 1 || argc == 2 || argc == 7;
    if (!is_num_params_valid) {
        throw std::invalid_argument("Invalid number of input parameters");
    }

    if (argc == 2) {
        threshold = decode_threshold(string(argv[1]));
        type = ParamsType::ThresholdOnly;
    }
    else if (argc == 7) {
        reference_folder = argv[1];
        compare_folder = argv[2];
        masks_folder = argv[3];
        threshold = decode_threshold(string(argv[4]));
        diff_folder = generate_diff_path(string(argv[5]));
        reports_folder = argv[6];
        type = ParamsType::FullParams;
    }
}

std::filesystem::path Parameters::generate_diff_path(const string path)
{
    return path + "\\differences";
}

unsigned char Parameters::decode_threshold(const string argument)
{
    int value{0};
    try {
        value = std::stoi(argument);
    }
    catch (std::exception ex) {
        throw std::invalid_argument("Failed to decode threshold value.");
    }

    if (value < 0 || value > 255)
        throw std::invalid_argument("Threshold " + std::to_string(value)
                                    + " out of accepted range [0,255].");

    return static_cast<unsigned char>(value);
}


void Parameters::print_cmd_syntax()
{
    std::cout << "Syntax: \n"
                 "1. diffim.exe\n"
                 "2. diffim.exe threshold\n"
                 "3. diffim.exe \"reference_folder\" \"compare_folder\" "
                 "\"masks_folder\" \"threshold\" \"OUT_diff_folder\" "
                 "\"OUT_report_folder\"  \n"
                 

                 "\n1. When used with 0 parameters, default values and local "
                 "folders are used: \n"
                 " INPUT:\n"
                 "   reference folder:  .\\input\\references\\\n"
                 "   compared images folder:    .\\input\\images\\\n"
                 "   masks folder:      .\\input\\masks\\\n"
                 "   threshold:         0\n\n"
                 " OUTPUT:\n"
                 "   differences folder:   .\\output\\differences\\\n"
                 "   reports:        .\\output\\ comparison.json and comparison.csv\n"

                 "\n2. When used with 1 parameter, the default values and "
                 "folders from 1 "
                 "apply but the threshold is overwritten.\n"
                 "\n\n";
}
