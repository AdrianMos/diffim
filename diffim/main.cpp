// main.cpp : Program execution begins and ends there.
#include "pch.h"

#include <memory>
#include "ComparableEntity.h"
#include "FolderScanner.h"
#include "ImageComparer.h"
#include "Parameters.h"
#include "reporters\IReporter.h"
#include "reporters\JsonReporter.h"
#include "reporters\TabReporter.h"
#include "utils.h"


void save_reports(std::vector<ComparableEntity>& items, Statistics statistics,
                  const Parameters& params);
Statistics compute_statistics(std::vector<ComparableEntity>& items);


int main(int argc, char** argv)
{
    try {
        print_app_title();

        Parameters params;
        params.load_from_args(argc, argv);
        params.print();

        print_separator();

        // App not started in full params mode => create default folder structure
        // to help the user in placing the images he wants to compare (e.g. masks
        // folder, referece images folder)
        if (params.type != Parameters::ParamsType::FullParams)
            create_input_folders(params);

        check_input_folders_existance(params);

        FolderScanner scanner{params};
        std::vector<ComparableEntity> items = scanner.scan();


        create_output_folders(params);

        ImageComparer comparer{params.show_images_while_processing};
        comparer.compare_all(items);


        Statistics statistics = compute_statistics(items);

        save_reports(items, statistics, params);

        statistics.print();
        print_separator();
    }
    catch (const std::invalid_argument& e) {
        std::cout << "\nERROR: invalid argument exception: " << e.what()
                  << "\n\n";
        Parameters::print_cmd_syntax();
        exit(EXIT_FAILURE);
    }
    catch (const std::exception& e) {
        std::cout << "\nERROR: " << e.what() << "\n\n";
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}


void save_reports(std::vector<ComparableEntity>& items, Statistics statistics,
                  const Parameters& params)
{
    std::cout << "\nReports: \n";

    // For now we generate two report types (json & tab seprated file)
    std::vector<std::unique_ptr<IReporter>> reporters;
    reporters.emplace_back(std::make_unique<JsonReporter>(statistics));
    reporters.emplace_back(std::make_unique<TabReporter>());

    for (auto& reporter : reporters) {
        auto path = reporter->generate_report_path(params.reports_folder);
        reporter->save(items, path, params);
        std::cout << "  " << path << "\n";
    }
}

Statistics compute_statistics(std::vector<ComparableEntity>& items)
{
    Statistics statistics;
    std::for_each(items.begin(), items.end(), [&](ComparableEntity& item) {
        statistics.add_status(item.status);
    });
    return statistics;
}
