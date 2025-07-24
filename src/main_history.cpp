#include <iostream>
#include <string>
#include <filesystem>
#include <queue>
#include <vector>

#include <tclap/CmdLine.h>

#include "data_structures/graph.h"
#include "metadata/dependencies.h"
#include "utils.h"

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

// using namespace EWOPE;
using namespace TCLAP;

int main(int argc, char** argv)
{
    std::cout << std::endl;
    std::cout << "########### STARTING EWOPE-HISTORY ..." << std::endl;
    std::cout << std::endl;

    std::string app_name = "history"; //app name

    std::string input_json;
    std::string workflow_dir;

    std::string ext = ".json"; //default extension for json files;

    try {
        CmdLine cmd("EWoPe = Embeddable WOrkflow PErsistence; History", ' ', "version 0.0");

        // ---------------------------------------------------------------------------------------------------------
        // MAIN FUNCTIONALITIES:

        // Option 0. New project creation
        // SwitchArg projectCreation           ("N", "new_project", "Creation new project", cmd, false); //booleano
        // ValueArg<std::string> projectFolder ("p", "pdir", "Project directory", true, "Directory", "path", cmd);

        ValueArg<std::string> setJSON       ("j", "json", "Set json file", true, "path", "string", cmd);

        ValueArg<std::string> workflowDir   ("w", "workflow", "Set workflow directory", false, "path", "string", cmd);
        SwitchArg setBackInfo               ("b", "back", "Set JSON history (recursively - back)", cmd, false); //booleano
        SwitchArg setForwardInfo            ("f", "forward", "Set JSON history (recursively - forward)", cmd, false); //booleano
        SwitchArg setMoreInfo               ("m", "more", "Set JSON history (recursively - forward) and commands", cmd, false); //booleano

        // ---------------------------------------------------------------------------------------------------------
        // PARSING:

        // Parse the argv array.
        cmd.parse(argc, argv);

        if(get_extension(setJSON.getValue()).compare(".json") != 0)
        {
            std::cout << "ERROR. File format not correct. Only JSON file are supported!" << std::endl;
            exit(1);
        }

        std::cout << "Loading file ... " << setJSON.getValue() << std::endl;
        std::cout << std::endl;

        std::string root_project = "";

        if (workflowDir.isSet())
        {
            root_project = workflowDir.getValue();
            if(root_project.back() != sep[0])
                root_project += sep;
        }

        // if(setJSON.getValue().find("out/") != std::string::npos)
        //     root_project = setJSON.getValue().substr(0, setJSON.getValue().find("out/"));

        std::cout << std::endl;
        std::cout << "### JSON GENERAL FEATURES ..." << std::endl;
        // std::cout << "JSON file root: " << root_project << std::endl;
        std::cout << std::endl;

        std::vector<std::string> deps, commands;
        if(setBackInfo.isSet())
        {
            //if(findDeps_from_JSON(setJSON.getValue()))
            deps = get_from_JSON(setJSON.getValue(), "dependencies");
            if(deps.size() == 0)
            {
                std::cout << "NO dependencies are found for file: " << setJSON.getValue() << std::endl;
                exit(1);
            }

            std::queue<std::string> queue;
            for(size_t i=0; i< deps.size(); i++)
                queue.push(deps.at(i));

            while (!queue.empty())
            {
                std::string curr = queue.front();
                std::cout << "---> " << curr << std::endl;
                queue.pop();

                deps.clear();
                if(curr.find(".json") != std::string::npos)
                    deps = get_from_JSON( root_project + curr, "dependencies");

                std::string indent = "\t";
                if(deps.size() > 0)
                {
                    for(size_t i=0; i< deps.size(); i++)
                        std::cout << indent + "---> " << deps.at(i) << std::endl;
                }
                else
                    std::cout << indent + "---> " << "NO dependencies are found." << std::endl;

                std::cout << std::endl;

                for(size_t i=0; i< deps.size(); i++)
                    queue.push(deps.at(i));
            }

        }


        if(setForwardInfo.isSet() && setMoreInfo.isSet())
        {
            std::deque<int> n_deps, level;
            std::deque<std::string> deque, deque_com;
            std::queue<std::string> queue;

            if (workflowDir.isSet())
            {
                filesystem::path rel_path = filesystem::relative(setJSON.getValue(), workflowDir.getValue());
                std::cout << "JSON file: " << rel_path << std::endl;
                queue.push(rel_path.string());
            }
            else
                queue.push(setJSON.getValue());

            int id_level = 0;
            level.push_back(id_level);


            while (!queue.empty())
            {
                std::string curr = queue.front();
                std::string curr_com;

                //if(filesystem::exists(root_project + curr) )
                if(curr.find(".json") != std::string::npos)
                    curr_com = get_from_JSON(curr,"commands").at(0);
                //curr_com = getCom_from_JSON(root_project + curr).at(0);

                queue.pop();
                //queue_com.pop();
                deque.push_back(curr);
                deque_com.push_back(curr_com);

                deps.clear();
                if(curr.find(".json") != std::string::npos)
                    deps = get_from_JSON(root_project + curr, "dependencies");

                n_deps.push_back(deps.size());

                if(deps.size() > 0)
                {
                    id_level++;
                    for(size_t i=0; i< deps.size(); i++)
                    {
                        queue.push(deps.at(i));
                        level.push_back(id_level);
                    }
                }
            }

            int k_last = 1;
            std::vector<EWOPE::Edge> edges;
            std::cout << "Creating graph ..." << std::endl;
            for(int j=0; j< deque.size(); j++)
            {
                int n_deps_node = n_deps.at(j);

                std::cout << "DEQUE: " << deque.at(j) << "; ";
                std::cout << "LEVEL: " << level.at(j) << "; ";
                std::cout << "DEPS: " << n_deps_node << "; ";
                std::cout << "INDEX_NODE: " << j << std::endl;

                if(n_deps_node != 0)
                {
                    for(int k=k_last; k< n_deps_node + k_last; k++)
                    {
                        int pos = j+k;

                        if(pos >= deque.size())
                            pos = deque.size();

                        EWOPE::Edge edge = {j, pos};
                        edges.push_back(edge);
                    }
                }

                k_last = k_last + n_deps.at(j) - 1;
            }
            std::cout << "Creating graph ... COMPLETED." << std::endl;
            std::cout << std::endl;


            // construct graph
            EWOPE::Graph graph(edges, edges.size()+1);

            // print adjacency list representation of a graph
            printGraph2(graph, edges.size()+1, deque, deque_com);

        }


        if(setForwardInfo.isSet() && !setMoreInfo.isSet())
        {

            std::cout << std::endl << "FORWARD -----------------------------------------" << std::endl << std::endl;
            std::deque<int> n_deps, level;
            std::deque<std::string> deque;
            std::queue<std::string> queue;

            if (workflowDir.isSet())
            {
                filesystem::path rel_path = filesystem::relative(setJSON.getValue(), workflowDir.getValue());
                std::cout << "JSON file: " << rel_path << std::endl;
                queue.push(rel_path.string());
            }
            else
                queue.push(setJSON.getValue());

            int id_level = 0;
            level.push_back(id_level);

            while (!queue.empty())
            {
                std::string curr = queue.front();
                // std::cout << " curr ---> " << curr << std::endl;
                queue.pop();
                deque.push_back(curr);

                deps.clear();
                if(curr.find(".json") != std::string::npos)
                    deps = get_from_JSON(root_project + curr, "dependencies");

                n_deps.push_back(deps.size());

                //std::string indent = "\t";
                if(deps.size() > 0)
                {
                    id_level++;
                    for(size_t i=0; i< deps.size(); i++)
                    {
                        queue.push(deps.at(i));
                        level.push_back(id_level);
                    }
                }
            }

            int k_last = 1;
            std::vector<EWOPE::Edge> edges;
            std::cout << "Creating graph ..." << std::endl;
            for(int j=0; j< deque.size(); j++)
            {
                int n_deps_node = n_deps.at(j);

                std::cout << "DEQUE: " << deque.at(j) << "; ";
                std::cout << "LEVEL: " << level.at(j) << "; ";
                std::cout << "DEPS: " << n_deps_node << "; ";
                std::cout << "INDEX_NODE: " << j << std::endl;

                if(n_deps_node != 0)
                {
                    for(int k=k_last; k< n_deps_node + k_last; k++)
                    {
                        int pos = j+k;

                        if(pos >= deque.size())
                            pos = deque.size();

                        EWOPE::Edge edge = {j, pos};
                        edges.push_back(edge);
                    }
                }

                k_last = k_last + n_deps.at(j) - 1;
            }
            std::cout << "Creating graph ... COMPLETED." << std::endl;
            std::cout << std::endl;

            // construct graph
            EWOPE::Graph graph(edges, edges.size()+1);

            // print adjacency list representation of a graph
            printGraph2(graph, edges.size()+1, deque);
        }

        std::cout << std::endl;
        std::cout << "Printing history of JSON: " << setJSON.getValue() << " COMPLETED." << std::endl;


    }
    catch (ArgException &e)  // catch exceptions
    {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    }



}
