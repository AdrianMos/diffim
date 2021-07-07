#include "..\pch.h"

#include "TabReporter.h"


void TabReporter::save(std::vector<ComparableEntity>& data,
                       const fs::path& report_path,
                       const Parameters& params)
{
    ofstream file;
    file.open(report_path);

    file << "File Name\tResult\tFolder\n";

    for (auto& result : data) {
        string name
            = result.relative_path.filename().replace_extension("").string();
        string status = convert_status_to_string(result.status);
        string folder = result.relative_path.parent_path().string();

        file << name << "\t" << status << "\t" << folder << "\n";
    }
    file.close();
}

fs::path TabReporter::generate_report_path(const fs::path& report_folder)
{
    return (report_folder / "comparison.tsv");
}
