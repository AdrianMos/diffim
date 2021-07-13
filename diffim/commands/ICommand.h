#pragma once
#include "..\ComparableEntity.h"
#include "..\Parameters.h"


class ICommand {
 public:
    virtual void execute() = 0;
};