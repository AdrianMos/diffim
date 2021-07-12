#include "..\pch.h"

#include "CsvReporter.h"


void CsvReporter::save(const std::vector<ComparableEntity>& data,
                       const fs::path& report_path,
                       const Parameters& params)
{
    ofstream file;
    file.open(report_path);

    file << "File Name,Result,Folder\n";

    for (auto& result : data) {
        string name
            = result.relative_path.filename().replace_extension("").string();
        string status = convert_status_to_string(result.status);
        string folder = result.relative_path.parent_path().string();

        file << name << "," << status << "," << folder << "\n";
    }
    file.close();
}

fs::path CsvReporter::generate_report_path(const fs::path& report_folder) const
{
    return (report_folder / "comparison.csv");
}
