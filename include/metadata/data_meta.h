#ifndef DATA_META_H
#define DATA_META_H

#include <string>
#include <vector>

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

#include "data_structures/project.h"
#include "data_structures/info_data.h"


namespace EWOPE
{
    class DataMeta;
}


///
/// \brief The EWOPE::DataMeta class
///
class EWOPE::DataMeta
{
public:

    struct CSVFile
    {
        std::string filename;
        std::string delimiter;

        // Add any other additional descriptive info

        #ifdef EWOPE_USES_CEREAL
        template <class Archive>
        void serialize( Archive & ar )
        {
            ar (CEREAL_NVP(filename));
            ar (CEREAL_NVP(delimiter));
        }

        template <class Archive>
        void deserialize( Archive & ar )
        {
            ar (CEREAL_NVP(filename));
            ar (CEREAL_NVP(delimiter));
        }
        #endif

        void setFilename        (const std::string &d)       { filename = d; }
        void setDelimiter       (const std::string &d)       { delimiter = d; }

    };

    struct DataFormat
    {
        int      n_variables = 0;
        int      n_accepted_variables = 0;


        // Add any other additional descriptive info

        #ifdef EWOPE_USES_CEREAL
        template <class Archive>
        void serialize( Archive & ar )
        {
            ar (CEREAL_NVP(n_variables));
            ar (CEREAL_NVP(n_accepted_variables));
        }

        template <class Archive>
        void deserialize( Archive & ar )
        {
            ar (CEREAL_NVP(n_variables));
            ar (CEREAL_NVP(n_accepted_variables));
        }
        #endif
    };




    // Get Methods
    const EWOPE::Project     &getProject    () const    { return  project; }

    const std::vector<std::string> &getCommands () const    { return commands;}
    const std::string &getCommand (const unsigned int i) const { return commands.at(i); }

    const EWOPE::InfoData    &getInfoData   () const    { return infodata; }

    const CSVFile           &getCSVFile    () const    { return  csvfile; }
    const DataFormat        &getDataFormat () const    { return  dataformat; }




    // Set Methods
    void setProject     (const EWOPE::Project &d)    { project = d; }
    void setCommands    (const std::vector<std::string> &d) { commands = d; }

    void setInfoData    (const EWOPE::InfoData &d)   { infodata = d; }

    void setCSVFile     (const CSVFile &d)          { csvfile = d; }
    void setDataFormat  (const DataFormat &d)       { dataformat = d; }


    // Additional Methods
    bool read  (const std::string filename);
    bool write (const std::string filename);




#ifdef EWOPE_USES_CEREAL
    template <class Archive>
    void serialize( Archive & ar )
    {
        ar (CEREAL_NVP(project));
        ar (CEREAL_NVP(commands));
        ar (CEREAL_NVP(infodata));
        ar (CEREAL_NVP(csvfile));
        ar (CEREAL_NVP(dataformat));
    }

    template <class Archive>
    void deserialize( Archive & ar )
    {
        ar (CEREAL_NVP(project));
        ar (CEREAL_NVP(commands));
        ar (CEREAL_NVP(infodata));
        ar (CEREAL_NVP(csvfile));
        ar (CEREAL_NVP(dataformat));
    }
#endif

private:

    EWOPE::Project project;
    std::vector<std::string> commands;
    EWOPE::InfoData infodata;

    CSVFile csvfile;
    DataFormat dataformat;



    bool readConfFileJSON   (const std::string filename);
    bool writeConfFileJSON  (const std::string filename) ;
};



#ifndef STATIC_EWOPE
#include "data_meta.cpp"
#endif

#endif // DATA_META_H
