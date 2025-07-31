/********************************************************************************
*  This file is part of EWoPE                                                   *
*  Copyright(C) 2025: Daniela Cabiddu, Marianna Miola                           *
*                                                                               *
*  Author(s):                                                                   *
*                                                                               *
*     Daniela Cabiddu (daniela.cabiddu@cnr.it)                                  *
*     Marianna Miola (marianna.miola@cnr.it)                                    *
*                                                                               *
*     Italian National Research Council (CNR)                                   *
*     Institute for Applied Mathematics and Information Technologies (IMATI)    *
*     Via de Marini, 6                                                          *
*     16149 Genoa,                                                              *
*     Italy                                                                     *
*                                                                               *
*  This program is free software: you can redistribute it and/or modify it      *
*  under the terms of the GNU General Public License as published by the        *
*  Free Software Foundation, either version 3 of the License, or (at your       *
*  option) any later version.                                                   *
*                                                                               *
*  This program is distributed in the hope that it will be useful, but          *
*  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY   *
*  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for  *
*  more details.                                                                *
*                                                                               *
*  You should have received a copy of the GNU General Public License along      *
*  with this program. If not, see <https://www.gnu.org/licenses/>.              *
*                                                                               *
*********************************************************************************/

#include <filesystem>
#include <iostream>
#include <string>

#include "metadata/metadata.h"
#include "metadata/extended/mesh_metadata.h"

#include <tclap/CmdLine.h>

//for filesystem
#ifdef __APPLE__
    using namespace std::__fs;
#else
    using namespace std;
#endif

int main(int argc, char **argv)
{

    // std::string proj_name = "proj";
    // std::string proj_path = std::filesystem::current_path().string();
    std::string command_line;
    std::vector<std::string> inputs ;
    std::vector<std::string> outputs;
    std::vector<std::string> command_lines ;


    // Wrap everything in a try block.  Do this every time,
    // because exceptions will be thrown for problems.
    try {

        // Define the command line object, and insert a message
        // that describes the program. The "Command description message"
        // is printed last in the help text. The second argument is the
        // delimiter (usually space) and the last one is the version number.
        // The CmdLine object parses the argv array based on the Arg objects
        // that it contains.
        TCLAP::CmdLine cmd("Command description message", ' ', "0.9");

        // Define a value argument and add it to the command line.
        // A value arg defines a flag and a type of value that it expects,
        // such as "-n Bishop".
        TCLAP::ValueArg<std::string> commandsArg("c", "command", "Command line", true, "", "string");
        TCLAP::MultiArg<std::string> inputsArg("i", "in", "Dependencies (inputs)", true, "string" );
        TCLAP::MultiArg<std::string> outputsArg("o", "out", "Outputs", true, "string" );

        // Add the argument nameArg to the CmdLine object. The CmdLine object
        // uses this Arg to parse the command line.
        cmd.add( commandsArg );
        cmd.add( inputsArg );
        cmd.add( outputsArg );

        // Parse the argv array.
        cmd.parse( argc, argv );

        command_line = commandsArg.getValue();
        inputs = inputsArg.getValue();
        outputs = outputsArg.getValue();

    }
    catch (TCLAP::ArgException &e)  // catch exceptions
    {
        std::cerr << e.error() << ": " << e.what() << std::endl;
        exit(1);
    }

    std::vector<std::string> deps;

    for (const std::string &s : inputs)
    {
        // check input existence
        if (!std::filesystem::exists(std::filesystem::path(s)))
        {
            std::cerr << "Input " << s << " does not exists. Check." << std::endl;
            exit(1);
        }

        deps.push_back(s.substr(0, s.find_last_of(".")) + ".json");
    }

    //// Run Executable.....
    int returnCode = system(command_line.c_str());

    if (returnCode != 0)
    {
        std::cout << "Command execution failed or returned non-zero: " << returnCode << std::endl;
        exit(1);
    }
    else
    {
        std::cout << "Command executed successfully." << std::endl;
    }

    command_lines.push_back(command_line);

    for (const std::string &o : outputs)
    {
        if (!std::filesystem::exists(std::filesystem::path(o)))
        {
            std::cerr << "Output " << o << " does not exists. Check." << std::endl;
            continue;
            // exit(1);
        }

        if (std::filesystem::path(o).extension().compare(".off") == 0)
        {
            std::cout << "Output " << o << " is a mesh" << std::endl;
            MeshMetadata metadata;

            metadata.setCommands(command_lines);
            metadata.setDependencies(deps);

            std::ifstream of;
            of.open(o);

            std::string line;
            unsigned num_verts, num_edges, num_polys;
            std::getline(of, line);
            of >> num_verts >> num_polys >> num_edges;

            metadata.set_num_polys(num_polys);
            metadata.set_num_verts(num_verts);

            std::string out_json = o.substr(0, o.find_last_of(".")) + ".json";
            std::cout << "Writing " << out_json << " ... " << std::endl;
            metadata.write(out_json);
        }
        else
        {
            EWOPE::Metadata metadata;

            metadata.setCommands(command_lines );
            metadata.setDependencies(deps);

            std::string out_json = o.substr(0, o.find_last_of(".")) + ".json";
            std::cout << "Writing " << out_json << " ... " << std::endl;
            metadata.write(out_json);
        }
    }
}
