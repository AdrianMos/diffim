#include "InvalidCommand.h"

InvalidCommand::InvalidCommand(Parameters params) : _params(params)
{
}

void InvalidCommand::execute() 
{
    std::cout << "Invalid command.\n";
    _params.print_syntax();
    exit(EXIT_FAILURE);
}