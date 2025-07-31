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

#ifndef DATA_META_H
#define DATA_META_H

#include <string>
#include <vector>

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

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

    const std::vector<std::string> &getCommands () const    { return commands;}
    const std::string &getCommand (const unsigned int i) const { return commands.at(i); }

    const EWOPE::InfoData    &getInfoData   () const    { return infodata; }

    const CSVFile           &getCSVFile    () const    { return  csvfile; }
    const DataFormat        &getDataFormat () const    { return  dataformat; }

    // Set Methods
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
        ar (CEREAL_NVP(commands));
        ar (CEREAL_NVP(infodata));
        ar (CEREAL_NVP(csvfile));
        ar (CEREAL_NVP(dataformat));
    }

    template <class Archive>
    void deserialize( Archive & ar )
    {
        ar (CEREAL_NVP(commands));
        ar (CEREAL_NVP(infodata));
        ar (CEREAL_NVP(csvfile));
        ar (CEREAL_NVP(dataformat));
    }
#endif

private:

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
