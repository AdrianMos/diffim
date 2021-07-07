#pragma once
#include "..\pch.h"

#include "..\ComparableEntity.h"
#include "IReporter.h"

class TabReporter : public IReporter {
 public:
    void save(std::vector<ComparableEntity>& data, const fs::path& report,
              const Parameters& params);
    fs::path generate_report_path(const fs::path& report_folder);
};