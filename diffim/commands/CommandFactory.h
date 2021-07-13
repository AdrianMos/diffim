#pragma once

#include "..\Parameters.h"
#include "ICommand.h"

class CommandFactory {
 public:
    static std::unique_ptr<ICommand> create_command(const Parameters& params);

 private:
    CommandFactory();
};