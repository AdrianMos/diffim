#pragma once
#include "..\pch.h"

#include "..\ComparableEntity.h"
#include "IReporter.h"

class CsvReporter : public IReporter {
 public:
    void save(const std::vector<ComparableEntity>& data, const fs::path& report,
              const Parameters& params);
    fs::path generate_report_path(const fs::path& report_folder) const;
};