#pragma once

#include "..\Parameters.h"
#include "ICommand.h"

class HelpCommand : public ICommand {
 public:
    HelpCommand(Parameters param);
    void execute() override;
 
private:
    Parameters _params;
};