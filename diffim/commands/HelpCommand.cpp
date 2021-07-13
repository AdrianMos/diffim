#include "HelpCommand.h"


HelpCommand::HelpCommand(Parameters params) : _params(params)
{
}

void HelpCommand::execute() 
{
    _params.print_syntax();
    _params.print_examples();
    exit(EXIT_FAILURE);
}