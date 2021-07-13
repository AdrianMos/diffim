#pragma once

#include "..\ComparableEntity.h"
#include "..\Parameters.h"
#include "..\Statistics.h"
#include "ICommand.h"

class CompareImagesCommand : public ICommand {
 public:
    CompareImagesCommand(Parameters param);
    void execute() override;

 private:
    Parameters _params;

    Statistics compute_statistics(std::vector<ComparableEntity>& items);
    void save_reports(std::vector<ComparableEntity>& items,
                      Statistics statistics, const Parameters& params);

    void create_input_folders(const Parameters& params);
    void create_output_folders(const Parameters& params);
    void check_input_folders_existance(const Parameters& params);
};