#include "CompareImagesCommand.h"
#include "../utils.h"

#include "../ComparableEntity.h"
#include "../FolderScanner.h"
#include "../ImageComparer.h"
#include "../Parameters.h"
#include "../reporters\CsvReporter.h"
#include "../reporters\IReporter.h"
#include "../reporters\JsonReporter.h"


CompareImagesCommand::CompareImagesCommand(Parameters params) : _params(params)
{
}

void CompareImagesCommand::execute()
{
    _params.print();

    print_separator();

    // App not started in full _params mode => create default folder structure
    // to help the user in placing the images he wants to compare (e.g. masks
    // folder, referece images folder)
    if (_params.type() != Parameters::ParamsType::FullParams)
        create_input_folders(_params);

    check_input_folders_existance(_params);

    FolderScanner scanner{_params};
    std::vector<ComparableEntity> items = scanner.scan();

    create_output_folders(_params);

    ImageComparer comparer{_params.show_images_while_processing};
    comparer.compare_all(items);


    Statistics statistics = compute_statistics(items);

    save_reports(items, statistics, _params);

    statistics.print();
}


Statistics CompareImagesCommand::compute_statistics(
    std::vector<ComparableEntity>& items)
{
    Statistics statistics;
    std::for_each(items.begin(), items.end(), [&](ComparableEntity& item) {
        statistics.add_status(item.status);
    });
    return statistics;
}

void CompareImagesCommand::save_reports(std::vector<ComparableEntity>& items,
                                        Statistics statistics,
                                        const Parameters& params)
{
    std::cout << "\nReports: \n";

    // For now we generate two report types (json & tab seprated file)
    std::vector<std::unique_ptr<IReporter>> reporters;
    reporters.emplace_back(std::make_unique<JsonReporter>(statistics));
    reporters.emplace_back(std::make_unique<CsvReporter>());

    for (auto& reporter : reporters) {
        auto path = reporter->generate_report_path(params.reports_folder);
        reporter->save(items, path, params);
        std::cout << "  " << path << "\n";
    }
}


void CompareImagesCommand::check_input_folders_existance(const Parameters& p)
{
    if (!fs::exists(p.reference_folder)) {
        throw std::invalid_argument("The reference folder does not exist!");
    }

    if (!fs::exists(p.images_folder)) {
        throw std::invalid_argument("The images folder does not exist!");
    }
}


void CompareImagesCommand::create_output_folders(const Parameters& p)
{
    if (fs::exists(p.diff_folder)) {
        fs::remove_all(p.diff_folder);
    }

    if (!fs::create_directories(p.diff_folder)) {
        std::cout << "\nFailed to create output folders.\n";
        throw;
    }
}


void CompareImagesCommand::create_input_folders(const Parameters& p)
{
    try {
        fs::create_directories(p.reference_folder);
        fs::create_directories(p.images_folder);
        fs::create_directories(p.masks_folder);
    }
    catch (...) {
        std::cout << "\nFailed to create input folders.\n";
        throw;
    }
}
