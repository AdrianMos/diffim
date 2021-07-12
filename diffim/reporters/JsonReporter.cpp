#include "..\pch.h"

#include "..\JsonElem.h"
#include "JsonReporter.h"

using std::string;

JsonReporter::JsonReporter(Statistics statistics) : _statistics(statistics)
{
}

void JsonReporter::save(const std::vector<ComparableEntity>& data,
                        const fs::path& report_filepath,
                        const Parameters& params)
{
    JsonElem results("results", JsonElem::DataType::List);
    

    for (auto& compare : data) {
        results.add(JsonElem(
            "",
            {{"result", convert_status_to_string(compare.status)},
             {"threshold", compare.threshold},
             {"image", compare.image.string()},
             {"reference", compare.reference.string()},
             {"mask", compare.mask.string()},
             {"folder", compare.relative_path.parent_path().string()}            
            }));
    }


    JsonElem root("");
    JsonElem summary("summary",
                     {{"success", _statistics.total()==_statistics.identical() ? "True" : "False"},
                      {"images", params.images_folder.string()},
                      {"references", params.reference_folder.string()},
                      {"masks", params.masks_folder.string()},
                      {"threshold", params.threshold}});

    JsonElem stats("statistics",
                   {{"total comparisons", _statistics.total()},
                    {"identical", _statistics.identical()},
                    {"different", _statistics.different()},
                    {"missing", _statistics.missing()},
                    {"not compared", _statistics.not_compared()}});


        JsonElem summary2("summary",
                     {{"success", _statistics.total()==_statistics.identical() ? "True" : "False"},
                      {"images", params.images_folder.string()},
                      {"references", params.reference_folder.string()},
                      {"masks", params.masks_folder.string()},
                      {"threshold", params.threshold}});


    root.add(summary).add(stats).add(results);


    ofstream file;
    file.open(report_filepath);
    file << root.to_pritty_string(0);
    file.close();
}


fs::path JsonReporter::generate_report_path(const fs::path& report_folder) const
{
    return (report_folder / "comparison.json");
}
