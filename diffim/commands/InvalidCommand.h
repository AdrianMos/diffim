#pragma once

#include "..\Parameters.h"
#include "ICommand.h"

class InvalidCommand : public ICommand {
 public:
    InvalidCommand(Parameters param);
    void execute() override;

 private:
    Parameters _params;
};