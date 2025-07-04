#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <filesystem>

#include <tclap/CmdLine.h>
//#include <json.hpp>

//#include "muselib/reference_system/coordinate_systems.h"

#include "load_csv.h"

#include "utils.h"
#include "metadata/metadata.h"
#include "metadata/data_meta.h"

#include "data_structures/data.h"

#include "flag/flag.h"
#include "flag/check.h"
#include "flag/num_check.h"

//for filesystem
#ifdef __APPLE__
//#include <filesystem>
using namespace std::__fs;
#else
//#include <experimental/filesystem>
using namespace std;
#endif

#ifdef WIN32
const std::string sep = "\\";
#else
const std::string sep = "/";
#endif

using namespace EWOPE;
using namespace TCLAP;

int main(int argc, char** argv)
{
    std::cout << std::endl;
    std::cout << "########### STARTING MUSE-DATA ..." << std::endl;
    std::cout << std::endl;

    std::string app_name = "data"; //app name

    std::vector<std::string> list_csv;
    std::string output_folder = "";

    try {
        CmdLine cmd("MUSE = Modelling of Uncertainty as a Support of Environment; Data tool", ' ', "version 0.0");

        // ---------------------------------------------------------------------------------------------------------
        // MAIN FUNCTIONALITIES:

        // Option 0. New project creation
        // SwitchArg projectCreation           ("N", "new_project", "Creation new project", cmd, false); //booleano
        // ValueArg<std::string> projectFolder ("p", "pdir", "Project directory", true, "Directory", "path", cmd);

        TCLAP::MultiArg<std::string> inputsArg("i", "in", "Inputs", true, "string", cmd);

        ValueArg<std::string> outputFolderArg ("o", "out", "Output folder", false, "", "", cmd);

        // Option 0a. Project creation - optional: setting project EPSG
        ValueArg<std::string> setEPSG       ("", "setEPSG", "Set project EPSG", false, "Unknown", "authority", cmd);

        // Option 1. Project creation - optional: setting coordinate columns
        SwitchArg setIDXYZ                  ("S", "setIDXYZ", "Set n. column coordinate", cmd, false); //booleano
        ValueArg<int> Colid                 ("", "setID", "Set ID", false, 0, "int" , cmd);
        ValueArg<int> Colx                  ("", "setX", "Set coordinate x", false, 0, "int" , cmd);
        ValueArg<int> Coly                  ("", "setY", "Set coordinate y", false, 0, "int" , cmd);
        ValueArg<int> Colz                  ("", "setZ", "Set coordinate z", false, 0, "int" , cmd);

        // Option 2b. Converter function - optional: setting delimiter
        std::vector<std::string> allowedDel = {"DEFAULT", "COMMA"}; //default = ;
        ValuesConstraint<std::string> allowedValsD(allowedDel);
        ValueArg<std::string> Delimiter     ("", "setDel", "Set type of csv delimiter", false, "DEFAULT", &allowedValsD, cmd);
        allowedDel.clear();

        // Option 2a. Converter function - SINGLE DATASET
        SwitchArg converterFunction         ("C", "converter", "Converter data (csv format) into MUSE format", cmd, false); //booleano
        //UnlabeledValueArg<int> n_rowsHeader ("n_rows_header", "Number of header rows", false, 6, "int", cmd);

        // Option 2a. Option for variables check
        //ValueArg<double> scaleFactor        ("", "scale", "Set scale factor unity (only for compositional variables)", false, 1.0, "double", cmd);
        ValueArg<double> infLimit           ("", "inf", "Set inf limit", false, 0, "inf", cmd);
        ValueArg<double> supLimit           ("", "sup", "Set sup limit", false, 1, "sup", cmd);

        // Option 2a. Converter function - optional: setting flag row
        //    SwitchArg setFlagRow                ("F", "set_flag", "Set flag row", cmd, false); //booleano
        //    ValueArg<int> FlagRow               ("r", "row", "Set row ", false, 0, "row", cmd);

        // Option 3. Reading MUSE format
        SwitchArg readFunction              ("R", "read", "Reading MUSE format", cmd, false); //booleano
        ValueArg<std::string> Variable      ("v", "var", "Variable", false, "ALL_INPUT", "name", cmd);
        ValueArg<int> setNrealization       ("n", "nrealiz", "Set number of realization", false, 0, "int", cmd);

        // ---------------------------------------------------------------------------------------------------------
        // ADDITIONAL FUNCTIONALITIES:

        SwitchArg csvConversion             ("", "csv", "Saving file as csv", cmd, false); //booleano

        //    // Option 2a. Converter function - MULTI DATASET
        //    SwitchArg mergeDataset              ("M", "multi", "Merge dataset into CSV format", cmd, false); //booleano


        // ---------------------------------------------------------------------------------------------------------
        // PARSING:

        // Parse the argv array.
        cmd.parse(argc, argv);

        list_csv = inputsArg.getValue();

        if (outputFolderArg.isSet())
            output_folder=outputFolderArg.getValue();


        // ---------------------------------------------------------------------------------------------------------
        // SETTINGS:

        // 0) Commands
        std::cout << "###### Execution command ..." << std::endl;
        std::string command;
        std::cout << "Number of command arguments: " << argc << std::endl;

        filesystem::path abspath = argv[0];
        std::cout << "Absolute path: " << abspath << std::endl;

        for(int i=1; i< argc; i++)
        {
            std::string string = argv[i];
            if(string.find(abspath.generic_string()) != std::string::npos)
            {
                //std::cout << "Path: " << argv[i] << std::endl;

                filesystem::path path = argv[i];
                filesystem::path relpath = filesystem::relative(path, abspath);
                //std::cout << "Relative path: " << relpath << std::endl;

                if(relpath.string().length() > 1)
                    command += "./" + relpath.string();
                else
                    command += relpath.generic_string();
                command += " ";
            }
            else
            {
                command += argv[i];
                command += " ";
            }
        }
        std::cout << command << std::endl;
        std::cout << "###### ###### ###### ######" << std::endl;
        std::cout << std::endl;

        std::string ext = ".dat";
        if(csvConversion.isSet() == true)
            ext = ".csv";


        // ---------------------------------------------------------------------------------------------------------
        // STARTS:


        //L'utente può copiare i dati nella cartella "in" e procedere con la conversione

        // Option 1. Setting coordinate function
        if(setIDXYZ.isSet())
        {
            EWOPE::DataMeta datameta;

            char csv_delimiter;
            if(Delimiter.getValue().compare("DEFAULT") == 0) //DEFAULT (;) oppure COMMA
            {
                csv_delimiter = ';';

                std::cout << "WARNING: The default delimiter is ';'. Set --setDel for changing the type." << std::endl;
            }
            if(Delimiter.getValue().compare("COMMA") == 0) //DEFAULT (;) oppure COMMA
                csv_delimiter = ',';


            // // Check on input files (.csv)
            // if(filesystem::is_empty(in_folder))
            // {
            //     std::cerr << "\033[0;31mInput ERROR: Insert file.csv \033[0m" << std::endl;
            //     exit(1);
            // }
            // else
            {
                // std::vector<std::string> list_csv = get_files(in_folder, ".csv");

                EWOPE::InfoData info;

                for(size_t i=0; i< list_csv.size(); i++)
                {
                    if(Colid.getValue() > 0)
                        info.id_name = search_column_csv(list_csv.at(i), Colid.getValue(), csv_delimiter);

                    if(Colx.getValue() > 0)
                        info.x_name = search_column_csv(list_csv.at(i), Colx.getValue(), csv_delimiter);

                    if(Coly.getValue() > 0)
                        info.y_name = search_column_csv(list_csv.at(i), Coly.getValue(), csv_delimiter);

                    if(Colz.getValue() > 0)
                        info.z_name = search_column_csv(list_csv.at(i), Colz.getValue(), csv_delimiter);

                    //std::string filename = list_csv.at(i).substr(list_csv.at(i).find_last_of("/")+1, list_csv.at(i).length());

                    EWOPE::DataMeta::CSVFile csv;

                    std::string basename = get_basename(get_filename(list_csv.at(i)));

                    csv.setFilename(basename);
                    csv.setDelimiter(Delimiter.getValue());
                    datameta.setCSVFile(csv);

                    datameta.setInfoData(info);

                    std::string output_filename = csv.filename;
                    if (output_folder.length() > 0)
                    {
                        if (std::filesystem::exists(output_folder))
                            std::filesystem::create_directories(output_folder);

                        output_filename = output_folder + sep + basename;
                    }

                    if(list_csv.size() > 1)
                    {
                        datameta.write(output_filename + ".json");
                        std::cout << "\033[0;32mUpdating JSON file: "<< csv.filename << ".json \033[0m" << std::endl;
                    }
                    else
                    {
                        datameta.write(output_filename + ".json");
                        std::cout << "\033[0;32mUpdating JSON file: "<< csv.filename << ".json \033[0m" << std::endl;
                    }
                }
            }
        }



        // Option 2. Converter function
        if(converterFunction.isSet())
        {
            // std::vector<std::string> list_csv = get_files(in_folder, ".csv");

            char csv_delimiter;
            if(Delimiter.getValue().compare("DEFAULT") == 0) //DEFAULT (;) oppure COMMA
            {
                csv_delimiter = ';';
                std::cout << "WARNING: The default delimiter is ';'. Set --setDel for changing the type." << std::endl;
            }
            if(Delimiter.getValue().compare("COMMA") == 0) //DEFAULT (;) oppure COMMA
                csv_delimiter = ',';


            for(size_t i=0; i< list_csv.size(); i++) //per multidataset, fare prima un merge dei file .csv
            {
                // Input
                std::string filename = list_csv.at(i);
                int n_rows_header = 6;

                EWOPE::DataMeta datameta;
                datameta.read(get_basename(get_filename(filename)) + ".json");


                // Reading csv and storing into matrix_header/data
                std::vector<std::vector<std::string>> matrix_header;
                std::vector<std::vector<std::string>> matrix_data;
                read_csv_with_header(filename, n_rows_header, matrix_header, matrix_data, csv_delimiter); //opzione sul delimitatore da linea di comando; stessa cosa anche sul separatore decimale!

                size_t n_var = matrix_header[0].size();
                size_t n_files = 0; //numero file creati in formato MUSE

                // Active flag table
                std::vector<EWOPE::Flag> table;
                flagsTable(table);

                int flag_row = 3; //riga della matrice (contando da 1) dove si trova il flag
                //            if(setFlagRow.isSet())
                //                flag_row = FlagRow.getValue();

                // Preliminary check on values and creation of MUSE Format (json and data file)

                std::cout << "Conversion into MUSE format ..." << std::endl;
                std::cout << "###############################" << std::endl;

                for(size_t i=0; i<n_var; i++)
                {
                    std::vector<std::string> header_variable = extracting_kcolumn(matrix_header, i);

                    std::string str_flag = header_variable[flag_row-1]; //posizione flag: l'utente la conosce dato che ha costruito il csv!!
                    std::string str_unity = header_variable[1]; //posizione unità di misura

                    //Check su unità di misura
                    double scale_factor = 1.0; // da stabilire in base all'unità di misura (usato per ora solo per le composizionali)
                    if(str_unity.compare("%") == 0)
                        scale_factor = scale_factor * 100;
                    if(str_unity.compare("ppm") == 0)
                        scale_factor = scale_factor * 1e6; //10^6
                    if(str_unity.compare("ppb") == 0)
                        scale_factor = scale_factor * 1e9; //10^9

                    // Activation flags in table
                    flagActivation(table, str_flag);
                    // char prev_plus = '\0';
                    // if(str_flag.find('+'))
                    //     prev_plus = str_flag[str_flag.find('+')-1];

                    // if(str_flag.find('-'))
                    //     prev_plus = str_flag[str_flag.find('-')-1];
                    // std::cout << prev_plus << std::endl;
                    // ////////////////// ATTENZIONE: CONSIDERARE LA CASISTICA IN CUI NELLA STRINGA POSSONO ESSERCI PIÙ + O +E-


                    // Data vector to check (related to active flags)
                    int n_activeFlag = count_activeFlag(table); //conta il numero di flag attivi
                    std::vector<std::string> data_variable = extracting_kcolumn(matrix_data, i);

                    for(size_t j=0; j<table.size(); j++) //ho una tabella aggiornata con i flag attivi (relativi alla variabile)
                    {
                        if(table.at(j).activeFlag == true)
                            getPreliminaryCheck(table.at(j).charFlag, data_variable, table.at(j).check, scale_factor, infLimit.getValue(), supLimit.getValue()); //richiama la funzione relativa al check da fare sui valori
                    }

                    int n_passedCheck = count_passedCheck(table);
                    if(n_activeFlag == n_passedCheck) //se i check sono superati per tutti i flag attivi, allora costruisco il formato; altrimenti errore!
                    {
                        n_files++;

                        // Check on printable chars
                        for(size_t k=0; k<header_variable.size(); k++)
                        {
                            std::string str_printable = header_variable.at(k);
                            if(nchars_printable(str_printable) < str_printable.length())
                                header_variable.at(k) = string_printable(str_printable);
                        }


                        EWOPE::Data data;
                        data.setData(header_variable);
                        std::vector<EWOPE::Data> multidata;
                        multidata.push_back(data);

                        Metadata meta_input;
                        meta_input.setMultiData(multidata);
                        // meta_input.setProject(Project);

                        std::vector<std::string> excommands;
                        excommands.push_back(command);
                        meta_input.setCommands(excommands);

                        std::vector<std::string> deps;
                        filesystem::path realpath = filesystem::relative(filename, abspath);
                        deps.push_back(realpath.string());
                        meta_input.setDependencies(deps);

                        std::string output_filename = header_variable.at(0);
                        if (output_folder.length() > 0)
                        {
                            if (std::filesystem::exists(output_folder))
                                std::filesystem::create_directories(output_folder);

                            output_filename = output_folder + sep + header_variable.at(0);
                        }

                        // filesystem::create_directory(out_folder + "/metadata");
                        meta_input.write(/*out_folder + "/metadata/" + */output_filename + ".json");
                        //data.write(out_folder + "/metadata/" + header_variable.at(0) + ".json");

                        // filesystem::create_directory(out_folder + "/data");
                        save_data(/*out_folder + "/data/" + */output_filename + ".dat", data_variable);

                        std::cout << "\033[0;32mAll checks are passed. Creation of MUSE format for variable: " << header_variable.at(0) << "\033[0m" << std::endl;
                        std::cout << std::endl;
                    }
                    else
                    {
                        std::cerr << "\033[0;31mERROR with the creation of MUSE format for variable: " << header_variable.at(0) << "\033[0m" << std::endl;
                        std::cout << std::endl;
                    }
                    restoreTable(table);
                }

                std::cout << "###############################" << std::endl;
                std::cout << "Conversion into MUSE format ... COMPLETED." << std::endl;
                std::cout << std::endl;

                // Summary about conversion
                if(n_files == n_var)
                    std::cout << "\033[0;32mAll variables are converted into MUSE format.\033[0m" << std::endl; //CONVERTED OR ACCEPETED???
                else
                    std::cout << "\033[0;32m" << n_files << " on " << n_var << " variables are converted into MUSE format.\033[0m" << std::endl;
                std::cout << std::endl;


                EWOPE::DataMeta::DataFormat format;
                format.n_variables = n_var;
                format.n_accepted_variables = n_files;
                datameta.setDataFormat(format);

                std::vector<std::string> excommands;
                excommands.push_back(command);
                datameta.setCommands(excommands);

                std::string output_filename = get_basename(get_filename(filename));
                if (output_folder.length() > 0)
                {
                    if (std::filesystem::exists(output_folder))
                        std::filesystem::create_directories(output_folder);

                    output_filename = output_folder + sep + output_filename;
                }


                datameta.write(/*out_folder + "/" + */ output_filename + ".json");
                std::cout << "\033[0;32mUpdating JSON file: "<< /*out_folder + "/" +*/ get_basename(get_filename(filename)) << ".json\033[0m" << std::endl;

                matrix_data.clear();
                matrix_header.clear();
            }
        }



        // Option 2. Reading MUSE format
        // if(readFunction.isSet() && Variable.getValue().compare("ALL_INPUT") != 0)
        // {
        //     std::string path = get_path(Variable.getValue());
        //     std::string json_basename = get_basename(get_filename(Variable.getValue()));

        //     // Reading json file
        //     EWOPE::Metadata data;
        //     data.read(Variable.getValue());

        //     PlotStruct dataplot;
        //     std::vector<EWOPE::Data> vec_data = data.getMultiData();

        //     if(setNrealization.isSet())
        //     {
        //         EWOPE::Data d = vec_data.at(setNrealization.getValue());
        //         d.setType(d.flag);

        //         std::vector<std::string> textValues;
        //         readTextValues(get_basename(Variable.getValue()) + "_" + d.getDescription() + ext, textValues);
        //         d.setTextValues(textValues);

        //         DataSummaryMeta datasum_meta;
        //         datasum_meta.setData(d);

        //         DataSummary sum;
        //         sum.setSummary(d);
        //         datasum_meta.setSummary(sum);

        //         if(d.type == NUMBER)
        //         {
        //             dataplot.x.clear();

        //             size_t n_sample = d.text_values.size();

        //             // Active flag table
        //             std::vector<Flag> table;
        //             flagsTable(table);

        //             // String-double conversion
        //             for(size_t i =0 ; i<n_sample; i++)
        //             {
        //                 //vedo che flag è e faccio il check per entrambi i vettori x e y
        //                 double val = 0.0;
        //                 std::string val_tmp = d.text_values.at(i);

        //                 if(!val_tmp.empty() && val_tmp.compare("nd") !=0) //se la stringa non è vuota ed è diversa da nd
        //                 {
        //                     if(val_tmp.compare("*")!=0)
        //                     {
        //                         if(val_tmp.compare("NA")!=0)
        //                         {
        //                             flagActivation(table, d.getFlag());
        //                             int n_activeFlag = count_activeFlag(table); //conta il numero di flag attivi
        //                             for(size_t i=0; i<table.size(); i++) //ho una tabella aggiornata con i flag attivi (relativi alla variabile)
        //                             {
        //                                 if(table.at(i).activeFlag == true)
        //                                     table.at(i).check = getCheck(table.at(i).charFlag, val_tmp);
        //                             }
        //                             int n_passedCheck = count_passedCheck(table);
        //                             restoreTable(table);

        //                             if(n_activeFlag == n_passedCheck)
        //                             {
        //                                 val = std::stod(val_tmp);
        //                                 dataplot.x.push_back(val);
        //                             }
        //                         }
        //                     }
        //                 }
        //             }

        //             int n_conv_samples = dataplot.x.size(); //numero campioni convertiti da stringa a double
        //             if(n_conv_samples == 0)
        //                 std::cerr << "\033[0;31mERROR: All values are invalid! No statistical data summary.\033[0m" << std::endl;
        //             else
        //             {
        //                 std::cout << "Statistical data summary ..." << std::endl;
        //                 summary(dataplot.x);

        //                 Statistics stats;
        //                 stats.setStatistics(dataplot.x);
        //                 datasum_meta.setStatistics(stats);

        //                 if(getHistogram.isSet())
        //                 {
        //                     if(n_conv_samples >= setNMaxValues.getValue()) //numero di punti sufficiente per creare un grafico
        //                     {
        //                         hist_plot(dataplot, Project.name, d.getName() + " [" + d.getUnit() + "]", "Frequency", setNbins.getValue(), setNbins.isSet());
        //                         matplot::save(get_basename(Variable.getValue()), "jpeg");
        //                         matplot::cla();
        //                         std::cout << std::endl;
        //                     }
        //                     else
        //                         std::cerr << "\033[0;31mERROR: Not created histogram! Number of samples is < " << setNMaxValues.getValue() << ".\033[0m" << std::endl;
        //                 }
        //             }
        //         }

        //         else
        //             std::cout << "\033[0;33mWARNING: Histogram plot is irrelevant for data type.\033[0m" << std::endl;

        //         datasum_meta.write(get_basename(Variable.getValue()) + "_summ.json");
        //     }
        //     else
        //     {
        //         for(EWOPE::Data &d:vec_data)
        //         {
        //             d.setType(d.flag);

        //             std::vector<std::string> textValues;
        //             readTextValues(get_basename(Variable.getValue()) + "_" + d.getDescription() + ext, textValues);
        //             d.setTextValues(textValues);

        //             DataSummaryMeta datasum_meta;
        //             datasum_meta.setData(d);

        //             DataSummary sum;
        //             sum.setSummary(d);
        //             datasum_meta.setSummary(sum);

        //             if(d.type == NUMBER)
        //             {
        //                 dataplot.x.clear();

        //                 size_t n_sample = d.text_values.size();

        //                 // Active flag table
        //                 std::vector<Flag> table;
        //                 flagsTable(table);

        //                 // String-double conversion
        //                 for(size_t i =0 ; i<n_sample; i++)
        //                 {
        //                     //vedo che flag è e faccio il check per entrambi i vettori x e y
        //                     double val = 0.0;
        //                     std::string val_tmp = d.text_values.at(i);

        //                     if(!val_tmp.empty() && val_tmp.compare("nd") !=0) //se la stringa non è vuota ed è diversa da nd
        //                     {
        //                         if(val_tmp.compare("*")!=0)
        //                         {
        //                             if(val_tmp.compare("NA")!=0)
        //                             {
        //                                 flagActivation(table, d.getFlag());
        //                                 int n_activeFlag = count_activeFlag(table); //conta il numero di flag attivi
        //                                 for(size_t i=0; i<table.size(); i++) //ho una tabella aggiornata con i flag attivi (relativi alla variabile)
        //                                 {
        //                                     if(table.at(i).activeFlag == true)
        //                                         table.at(i).check = getCheck(table.at(i).charFlag, val_tmp);
        //                                 }
        //                                 int n_passedCheck = count_passedCheck(table);
        //                                 restoreTable(table);

        //                                 if(n_activeFlag == n_passedCheck)
        //                                 {
        //                                     val = std::stod(val_tmp);
        //                                     dataplot.x.push_back(val);
        //                                 }
        //                             }
        //                         }
        //                     }
        //                 }

        //                 int n_conv_samples = dataplot.x.size(); //numero campioni convertiti da stringa a double
        //                 if(n_conv_samples == 0)
        //                     std::cerr << "\033[0;31mERROR: All values are invalid! No statistical data summary.\033[0m" << std::endl;
        //                 else
        //                 {
        //                     std::cout << "Statistical data summary ..." << std::endl;
        //                     summary(dataplot.x);

        //                     Statistics stats;
        //                     stats.setStatistics(dataplot.x);
        //                     datasum_meta.setStatistics(stats);

        //                     if(getHistogram.isSet())
        //                     {
        //                         if(n_conv_samples >= setNMaxValues.getValue()) //numero di punti sufficiente per creare un grafico
        //                         {
        //                             hist_plot(dataplot, Project.name, d.getName() + " [" + d.getUnit() + "]", "Frequency", setNbins.getValue(), setNbins.isSet());
        //                             matplot::save(get_basename(Variable.getValue()), "jpeg");
        //                             matplot::cla();
        //                             std::cout << std::endl;
        //                         }
        //                         else
        //                             std::cerr << "\033[0;31mERROR: Not created histogram! Number of samples is < " << setNMaxValues.getValue() << ".\033[0m" << std::endl;
        //                     }
        //                 }
        //             }

        //             else
        //                 std::cout << "\033[0;33mWARNING: Histogram plot is irrelevant for data type.\033[0m" << std::endl;

        //             datasum_meta.write(get_basename(Variable.getValue()) + "_summ.json");
        //         }
        //     }

        //     std::cout << std::endl;
        //     std::cout << "\033[0;32mReading MUSE format and data analysis... COMPLETED.\033[0m" << std::endl;

        // }



        // // Option 2. Reading MUSE format
        // if(readFunction.isSet() && Variable.getValue().compare("ALL_INPUT") == 0)
        // {
        //     std::string abs_datadir = out_folder;
        //     std::vector<std::string> list_dir = get_directories(abs_datadir);
        //     if(list_dir.empty())
        //         list_dir.push_back(abs_datadir);

        //     int count_frame = 0;
        //     for(const std::string &l:list_dir)
        //     {
        //         count_frame++;

        //         filesystem::path dir = l;
        //         filesystem::path rel_datadir = filesystem::relative(dir, abs_datadir);

        //         std::string sum_folder = out_folder;
        //         if(rel_datadir.string().compare(".") != 0)
        //         {
        //             sum_folder += "/"+ rel_datadir.string();

        //             std::cout << std::endl;
        //             std::cout << "###########################" << std::endl;
        //             std::cout << "### NUMBER OF TIME FRAMES: " << list_dir.size() << std::endl;
        //             std::cout << "### TIME FRAME N° " << count_frame << " ON " << list_dir.size() << std::endl;
        //             std::cout << "### TIME FRAME NAME: " << rel_datadir.string() << std::endl;
        //             std::cout << std::endl;
        //         }
        //         sum_folder += "/summary";

        //         if(!filesystem::exists(sum_folder))
        //             filesystem::create_directory(sum_folder);

        //         std::vector<std::string> list_proj_json = get_files(l, ".json");
        //         if(list_proj_json.size() > 1)
        //         {
        //             std::cerr << "ERROR. Only a file JSON is expected!" << std::endl;
        //             exit(1);
        //         }

        //         // Definition of coordinate variables
        //         EWOPE::DataMeta datameta;
        //         datameta.read(list_proj_json.at(0));


        //         // Creation of data structure
        //         std::vector<Data> dataset; //struttura dati
        //         std::vector<std::string> list_json = get_files(l + "/metadata", ".json"); //gli devo passare la json_dir

        //         size_t n_var = list_json.size();
        //         for(size_t i=0; i< n_var; i++)
        //         {
        //             // Funzioni per estrarre la lista dei file contenuti in una cartella: utile per lavorare su tutti i file
        //             // Apertura multipla: gli devo dare la cartella dei json

        //             // Defining paths (json and data file)
        //             std::string json_path = list_json.at(i);

        //             std::string json_filename;
        //             json_filename = json_path.substr(json_path.find_last_of("/")+1, json_path.length());

        //             std::string basename = get_basename(json_filename);

        //             std::string data_filename = basename +".dat";
        //             std::string data_path = l +"/data/"+ data_filename;

        //             // Reading json file
        //             EWOPE::Metadata data;
        //             data.read(json_path);

        //             std::vector<EWOPE::Data> vec_data = data.getMultiData();

        //             if(!filesystem::exists(sum_folder + "/" + basename +".json"))
        //                 filesystem::copy(json_path, sum_folder + "/"+ basename +".json");

        //             for(EWOPE::Data &d:vec_data)
        //             {
        //                 d.setType(d.flag);

        //                 // Set id
        //                 if(d.getName() == datameta.getInfoData().id_name)
        //                     d.type = ID;

        //                 // Set coordinates
        //                 if(d.getName() == datameta.getInfoData().x_name || d.getName() == datameta.getInfoData().y_name || d.getName() == datameta.getInfoData().z_name)
        //                     d.type = COORDINATE; //settare quando leggo l'epsg!!

        //                 std::vector<std::string> textValues;
        //                 readTextValues(data_path, textValues);
        //                 d.setTextValues(textValues);

        //                 dataset.push_back(d);
        //             }

        //         }

        //         std::cout << "\033[0;32mCreating data stucture... COMPLETED.\033[0m"<< std::endl;
        //         std::cout << std::endl;

        //         PlotStruct dataplot;
        //         std::cout << "Reading MUSE format and data analysis ..." << std::endl;
        //         for(size_t i=0; i<dataset.size(); i++)
        //         {
        //             DataSummaryMeta datasum_meta;

        //             Data var = dataset.at(i);
        //             datasum_meta.setData(var);

        //             DataSummary sum;
        //             sum.setSummary(var);
        //             datasum_meta.setSummary(sum);


        //             if(var.type == NUMBER)
        //             {
        //                 dataplot.x.clear();

        //                 size_t n_sample = var.text_values.size();

        //                 // Active flag table
        //                 std::vector<Flag> table;
        //                 flagsTable(table);

        //                 // String-double conversion
        //                 for(size_t i =0 ; i<n_sample; i++)
        //                 {
        //                     //vedo che flag è e faccio il check per entrambi i vettori x e y
        //                     double val = 0.0;
        //                     std::string val_tmp = var.text_values.at(i);

        //                     if(!val_tmp.empty() && val_tmp.compare("nd") !=0) //se la stringa non è vuota ed è diversa da nd
        //                     {
        //                         if(val_tmp.compare("*")!=0)
        //                         {
        //                             if(val_tmp.compare("NA")!=0)
        //                             {
        //                                 flagActivation(table, var.getFlag());
        //                                 int n_activeFlag = count_activeFlag(table); //conta il numero di flag attivi
        //                                 for(size_t i=0; i<table.size(); i++) //ho una tabella aggiornata con i flag attivi (relativi alla variabile)
        //                                 {
        //                                     if(table.at(i).activeFlag == true)
        //                                         table.at(i).check = getCheck(table.at(i).charFlag, val_tmp);
        //                                 }
        //                                 int n_passedCheck = count_passedCheck(table);
        //                                 restoreTable(table);

        //                                 if(n_activeFlag == n_passedCheck)
        //                                 {
        //                                     val = std::stod(val_tmp);
        //                                     dataplot.x.push_back(val);
        //                                 }
        //                             }
        //                         }
        //                     }
        //                 }

        //                 int n_conv_samples = dataplot.x.size(); //numero campioni convertiti da stringa a double
        //                 if(n_conv_samples == 0)
        //                     std::cerr << "\033[0;31mERROR: All values are invalid! No statistical data summary.\033[0m" << std::endl;
        //                 else
        //                 {
        //                     std::cout << "Statistical data summary ..." << std::endl;
        //                     summary(dataplot.x);

        //                     Statistics stats;
        //                     stats.setStatistics(dataplot.x);
        //                     datasum_meta.setStatistics(stats);

        //                     if(getHistogram.isSet() && n_conv_samples >= setNMaxValues.getValue()) //numero di punti sufficiente per creare un grafico
        //                     {
        //                         hist_plot(dataplot, Project.name, var.getName() + " [" + var.getUnit() + "]", "Frequency", setNbins.getValue(), setNbins.isSet());
        //                         matplot::save(sum_folder + "/" + var.getName(), "jpeg");
        //                         matplot::cla();
        //                         std::cout << std::endl;
        //                     }
        //                     else
        //                         std::cerr << "\033[0;31mERROR: Not created histogram! Number of samples is < " << setNMaxValues.getValue() << ".\033[0m" << std::endl;
        //                 }
        //             }

        //             else
        //                 std::cout << "\033[0;33mWARNING: Histogram plot is irrelevant for data type.\033[0m" << std::endl;

        //             datasum_meta.write(sum_folder + "/"+ var.getName() + ".json");
        //         }

        //         std::cout << std::endl;
        //         std::cout << "\033[0;32mReading MUSE format and data analysis... COMPLETED.\033[0m" << std::endl;
        //     }
        // }

    }
    catch (ArgException &e)  // catch exceptions
    {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    }

}
