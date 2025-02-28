#ifndef METADATA_H
#define METADATA_H

#include "data_structures/data.h"

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

#include <string>
#include <vector>

namespace EWOPE
{

class Metadata
{
public:

    // Get Methods
    // const EWOPE::Project     &getProject         ()          const    { return  project; }

    const std::vector<std::string> &getCommands ()          const    { return commands;}
    const std::string &getCommand (const unsigned int i)    const { return commands.at(i); }

    const std::vector<std::string> &getDeps     ()          const { return  dependencies; }
    const std::string &getDep (const unsigned int i)        const { return  dependencies.at(i); }

    // const std::vector<EWOPE::Data>  &getMultiData()          const    { return  data; }
    // const EWOPE::Data &getData (const unsigned int i)        const    { return  data.at(i); }


    // Set Methods
    // void setProject     (const EWOPE::Project &d)            { project = d; }
    void setCommands    (const std::vector<std::string> &d) { commands = d; }
    void setDependencies(const std::vector<std::string> &d) { dependencies = d; }
    void setMultiData   (const std::vector<EWOPE::Data> &d)  { data = d; }


    // Additional Methods
    bool read  (const std::string filename);
    bool write (const std::string filename);

    template <class Archive>
    void serialize( Archive & ar )
    {
        // ar (CEREAL_NVP(project));
        ar (CEREAL_NVP(commands));
        ar (CEREAL_NVP(dependencies));
        // ar (CEREAL_NVP(data));
    }

    template <class Archive>
    void deserialize( Archive & ar )
    {
        // ar (CEREAL_NVP(project));
        ar (CEREAL_NVP(commands));
        ar (CEREAL_NVP(dependencies));
        // ar (CEREAL_NVP(data));
    }


protected:

    // EWOPE::Project project;
    std::vector<std::string> commands;
    std::vector<std::string> dependencies;

    std::vector<EWOPE::Data> data;

    bool readConfFileJSON   (const std::string filename);
    bool writeConfFileJSON  (const std::string filename);

};

}


#ifndef STATIC_LIB
#include "metadata.cpp"
#endif

#endif // METADATA_H
