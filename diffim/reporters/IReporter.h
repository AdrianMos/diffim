#pragma once
#include "..\ComparableEntity.h"
#include "..\Parameters.h"


class IReporter {
 public:
	virtual void save(std::vector<ComparableEntity>& data, const fs::path& report, const Parameters& params) = 0;
    virtual fs::path generate_report_path(const fs::path& report_folder) = 0;
};