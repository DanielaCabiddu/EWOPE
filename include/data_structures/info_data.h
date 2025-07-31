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

#ifndef INFO_DATA_H
#define INFO_DATA_H

#include <string>

#include <cereal/archives/json.hpp>

namespace EWOPE
{
    class InfoData;
}

///
/// \brief The EWOPE::InfoData class: store general information about CSV input file and related conversion in MUSE DataFormat
///
class EWOPE::InfoData
{
    public:

    //std::string v_name = "Unknown";
    std::string x_name = "Unknown";
    std::string y_name = "Unknown";
    std::string z_name = "Unknown";
    std::string id_name = "Unknown";

    // Add any other additional descriptive info

    #ifdef EWOPE_USES_CEREAL
    template <class Archive>
    void serialize( Archive & ar )
    {
        //ar (CEREAL_NVP(v_name));
        ar (CEREAL_NVP(x_name));
        ar (CEREAL_NVP(y_name));
        ar (CEREAL_NVP(z_name));
        ar (CEREAL_NVP(id_name));
    }

    template <class Archive>
    void deserialize( Archive & ar )
    {
        ar (CEREAL_NVP(x_name));
        ar (CEREAL_NVP(y_name));
        ar (CEREAL_NVP(z_name));
        //ar (CEREAL_NVP(v_name));
        ar (CEREAL_NVP(id_name));
    }
    #endif

};

#endif // INFO_DATA_H
