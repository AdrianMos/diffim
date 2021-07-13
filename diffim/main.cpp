// main.cpp : Program execution begins and ends there.
#include "pch.h"

#include "Parameters.h"
#include "utils.h"

#include "commands/CommandFactory.h";


int main(int argc, char** argv)
{
    try {
        print_app_title();

        Parameters params;
        params.load_from_args(argc, argv);

        auto command = CommandFactory::create_command(params);
        command->execute();

        print_app_ending();
    }
    catch (const std::exception& e) {
        std::cout << "\nERROR: " << e.what() << "\n\n"; 
        Parameters::print_syntax();
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}