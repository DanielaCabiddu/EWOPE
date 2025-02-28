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
        cout << "Command execution failed or returned non-zero: " << returnCode << endl;
        exit(1);
    }
    else
    {
        cout << "Command executed successfully." << endl;
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
