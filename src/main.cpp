#include <iostream>
#include <filesystem>
#include <string>

#include <data_structures/project.h>

#include <metadata/metadata.h>
#include <metadata/data_meta.h>

#include <metadata/vario_meta.h>
#include <metadata/vario_methods.h>

//for filesystem
#ifdef __APPLE__
    using namespace std::__fs;
#else
    using namespace std;
#endif

int main(int argc, char **argv)
{
    MUSE::Project project;

    project.setName("name");
    project.setFolder("folder");

    project.write("project.json");

    // add data to project

    // input data
    MUSE::DataMeta metadata;
    metadata.setProject(project);

    MUSE::DataMeta::CSVFile csv_file;
    csv_file.setFilename("name.csv");
    csv_file.setDelimiter(" ");

    metadata.setCSVFile(csv_file);

    // /// check data and validation - input: metadata
    // update metadata
    // generate var_metadata

    std::vector<MUSE::Metadata> var_metadata;

    metadata.write("metadata.json");

    for (unsigned int v=0; v < var_metadata.size(); v++)
        var_metadata.at(v).write("var_meta_[v].json");


    // vario
    MUSE::VarioMeta vario_metadata;
    vario_metadata.setProject(project);

    vario_metadata.setInfoData(metadata.getInfoData());

    MUSE::VarioMeta::Processing vario_process_metadata;

    vario_process_metadata.v_name = "VAR_NAME";
    vario_process_metadata.declustering = "NO";
    vario_process_metadata.normal_score = "YES";

    vario_metadata.setProcessing(vario_process_metadata);

    MUSE::VarioMeta::InfoVariogram vario_setting_info;
    vario_setting_info.dimension = "2D";
    vario_setting_info.direction = "DIR";
    vario_setting_info.n_directions = 5;
    //....

    vario_metadata.setInfoVariogram(vario_setting_info);

    // run vario -
    //// INPUT vario_metadata
    /// OUTPUT update vario_metadata

    vario_metadata.write("vario_meta.json");


}
