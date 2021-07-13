#include "CommandFactory.h"
#include "HelpCommand.h"
#include "InvalidCommand.h"
#include "CompareImagesCommand.h"
#include "..\Parameters.h"

CommandFactory::CommandFactory()
{
}


std::unique_ptr<ICommand> CommandFactory::create_command(const Parameters& params)
{
    std::unique_ptr<ICommand> command = std::make_unique<InvalidCommand>(params);

    switch (params.type()) {
        case Parameters::ParamsType::HelpCommand:
            command = std::make_unique<HelpCommand>(params);
            break;

        case Parameters::ParamsType::DefaultParams:
        case Parameters::ParamsType::FullParams:
        case Parameters::ParamsType::ThresholdOnly:
            command = std::make_unique<CompareImagesCommand>(params);
            break;

        case Parameters::ParamsType::Unknown:
        default:
            break;       
    }

    return command;
 }

