#pragma once
#include "..\pch.h"

#include "..\ComparableEntity.h"
#include "..\Parameters.h"
#include "..\Statistics.h"
#include "IReporter.h"

class JsonReporter : public IReporter {
 public:
    JsonReporter(Statistics statistics);
    void save(std::vector<ComparableEntity>& data, const fs::path& report,
              const Parameters& params);
    fs::path generate_report_path(const fs::path& report_folder);

 private:
    Statistics _statistics;
};