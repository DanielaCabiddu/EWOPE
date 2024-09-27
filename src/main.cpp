#include <filesystem>
#include <iostream>
#include <string>

#include <metadata/metadata.h>

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
    std::vector<std::string> command_lines;
    std::vector<std::string> inputs ;

    std::vector<std::string> outputs;

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
        TCLAP::MultiArg<std::string> commandsArg("c","command","Command line",true, "string");
        TCLAP::MultiArg<std::string> inputsArg("i", "in", "Dependencies (inputs)", true, "string" );
        TCLAP::MultiArg<std::string> outputsArg("o", "out", "Outputs", true, "string" );

        // Add the argument nameArg to the CmdLine object. The CmdLine object
        // uses this Arg to parse the command line.
        cmd.add( commandsArg );
        cmd.add( inputsArg );
        cmd.add( outputsArg );

        // Parse the argv array.
        cmd.parse( argc, argv );

        command_lines = commandsArg.getValue();
        inputs = inputsArg.getValue();
        outputs = outputsArg.getValue();

    }
    catch (TCLAP::ArgException &e)  // catch exceptions
    {
        std::cerr << e.error() << ": " << e.what() << std::endl;
        exit(1);
    }

    std::vector<std::string> deps;

    for (const std::string s : inputs)
    {
        deps.push_back(s.substr(0, s.find_last_of(".")) + ".json");

        // check di esistenza e del caso di uno a molti
    }

    for (const std::string o : outputs)
    {

        Metadata metadata;

        metadata.setCommands(command_lines);
        metadata.setDependencies(deps);

        metadata.write(o.substr(0, o.find_last_of(".")) + ".json");
    }


}
