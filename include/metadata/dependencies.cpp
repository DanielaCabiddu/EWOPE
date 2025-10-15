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

#include "dependencies.h"

#include <fstream>


std::vector<std::string> get_from_JSON (const std::string &JSONfilename, const std::string &search)
{
    std::ifstream file_in;
    file_in.open(JSONfilename, std::fstream::out);
    if(!file_in.is_open())
    {
        std::cerr << "\033[0;31mError in file opening: " << JSONfilename << "\033[0m" << std::endl;
        exit(1);
    }

    std::vector<std::string> deps;
    std::string line;

    //std::string search = "dependencies";

    unsigned int curLine = 0;
    while(getline(file_in, line))
    {
        curLine++;
        if (line.find(search, 0) != std::string::npos)
        {
            //std::cout << "### Found: " << search << " at line: " << curLine << std::endl;
            //std::cout << line << std::endl;
            break;
        }
    }

    while(getline(file_in, line))
    {
        //itLine++;
        if (line.find("]", 0) == std::string::npos)
        {
            line.erase(remove(line.begin(), line.end(), ' '), line.end());
            line.erase(remove(line.begin(), line.end(), '"'), line.end());
            line.erase(remove(line.begin(), line.end(), ','), line.end());
            //std::cout << "found: " << line << std::endl;
            //cout << "found: " << line << " - line: " << itLine << endl;
            deps.push_back(line);
        }
        else
            break;
    }
    file_in.close();

    //std::cout << "Loading xyz file: " << JSONfilename << " ... COMPLETED." << std::endl;
    return deps;
}

// bool findDeps_from_JSON (const std::string &JSONfilename)
// {
//     bool find_deps = false;
//     std::vector<std::string> apps {"data", "geometry", "manipulate", "vario", "compute"};

//     std::string loc;
//     for(const std::string &name:apps)
//     {
//         if(JSONfilename.find(name) != std::string::npos)
//         {
//             loc = name;
//             break;
//         }
//     }

//     if(loc == apps[0])
//     {
//         //MUSE DATA META
//         MUSE::Metadata datameta;
//         datameta.read(JSONfilename);

//         if(datameta.getDeps().size() > 0)
//             find_deps = true;
//     }
//     else if(loc == apps[1] && JSONfilename.find("surf") != std::string::npos)
//     {
//         //MUSE GEOMETRY META
//         MUSE::SurfaceMeta surfmeta;
//         surfmeta.read(JSONfilename);

//         if(surfmeta.getDeps().size() > 0)
//             find_deps = true;
//     }
//     else if(loc == apps[1] && JSONfilename.find("volume") != std::string::npos)
//     {
//         //MUSE GEOMETRY META
//         MUSE::VolumeMeta volmeta;
//         volmeta.read(JSONfilename);

//         if(volmeta.getDeps().size() > 0)
//             find_deps = true;
//     }
//     else if(loc == apps[2])
//     {
//         //MUSE MANIPULATE META
//         MUSE::ExtractionMeta extrmeta;
//         extrmeta.read(JSONfilename);

//         if(extrmeta.getDeps().size() > 0)
//             find_deps = true;
//     }
//     else if(loc == apps[3])
//     {
//         //MUSE VARIO META
//         MUSE::VarioMeta variometa;
//         variometa.read(JSONfilename);

//         if(variometa.getDeps().size() > 0)
//             find_deps = true;
//     }
//     else if(loc == apps[4] && JSONfilename.find("_sgs") == std::string::npos)
//     {
//         //MUSE COMPUTE META
//         MUSE::ComputeMeta computemeta;
//         computemeta.read(JSONfilename);

//         if(computemeta.getDeps().size() > 0)
//             find_deps = true;
//     }
//     else if(loc == apps[4])
//     {
//         //MUSE DATA META
//         MUSE::Metadata datameta;
//         datameta.read(JSONfilename);

//         if(datameta.getDeps().size() > 0)
//             find_deps = true;
//     }
//     return find_deps;
// }


// std::vector<std::string> getDeps_from_JSON(const std::string &JSONfilename)
// {
//     std::vector<std::string> deps;
//     std::vector<std::string> apps {"data", "geometry", "manipulate", "vario", "compute"};

//     std::string loc;
//     for(const std::string &name:apps)
//     {
//         if(JSONfilename.find(name) != std::string::npos)
//         {
//             loc = name;
//             break;
//         }
//     }

//     std::string key0 = "samples_";
//     std::string key1 = "geom_";

//     if(loc == apps[0])
//     {
//         //MUSE DATA META
//         MUSE::Metadata datameta;
//         datameta.read(JSONfilename);

//         deps = datameta.getDeps();
//     }
//     else if(loc == apps[1] && JSONfilename.find("surf") != std::string::npos)
//     {
//         //MUSE GEOMETRY META
//         MUSE::SurfaceMeta surfmeta;
//         surfmeta.read(JSONfilename);

//         deps = surfmeta.getDeps();
//     }
//     else if(loc == apps[1] && JSONfilename.find("volume") != std::string::npos)
//     {
//         //MUSE GEOMETRY META
//         MUSE::VolumeMeta volmeta;
//         volmeta.read(JSONfilename);

//         deps = volmeta.getDeps();
//     }
//     else if(loc == apps[2] && JSONfilename.find(key0) != std::string::npos)
//     {
//         //MUSE MANIPULATE META
//         MUSE::ManipulateMeta extrmeta;
//         extrmeta.read(JSONfilename);

//         deps = extrmeta.getDeps();
//     }
//     else if(loc == apps[2] && JSONfilename.find(key1) != std::string::npos)
//     {
//         //MUSE MANIPULATE META
//         MUSE::ManipulateMeta extrmeta;
//         extrmeta.read(JSONfilename);

//         deps = extrmeta.getDeps();
//     }
//     else if(loc == apps[2])
//     {
//         //MUSE MANIPULATE META
//         MUSE::ExtractionMeta extrmeta;
//         extrmeta.read(JSONfilename);

//         deps = extrmeta.getDeps();
//     }
//     else if(loc == apps[3])
//     {
//         //MUSE VARIO META
//         MUSE::VarioMeta variometa;
//         variometa.read(JSONfilename);

//         deps = variometa.getDeps();
//     }
//     else if(loc == apps[4] && JSONfilename.find("_sgs") == std::string::npos)
//     {
//         //MUSE COMPUTE META
//         MUSE::ComputeMeta computemeta;
//         computemeta.read(JSONfilename);

//         deps = computemeta.getDeps();
//     }
//     else if(loc == apps[4])
//     {
//         //MUSE DATA META
//         MUSE::Metadata datameta;
//         datameta.read(JSONfilename);

//         deps = datameta.getDeps();
//     }
//     return deps;
// }

// std::vector<std::string> getCom_from_JSON(const std::string &JSONfilename)
// {
//     std::vector<std::string> deps;
//     std::vector<std::string> apps {"data", "geometry", "manipulate", "vario", "compute"};

//     std::string loc;
//     for(const std::string &name:apps)
//     {
//         if(JSONfilename.find(name) != std::string::npos)
//         {
//             loc = name;
//             break;
//         }
//     }

//     std::string key0 = "samples_";
//     std::string key1 = "geom_";

//     if(loc == apps[0])
//     {
//         //MUSE DATA META
//         MUSE::Metadata datameta;
//         datameta.read(JSONfilename);

//         deps = datameta.getCommands();
//     }
//     else if(loc == apps[1] && JSONfilename.find("surf") != std::string::npos)
//     {
//         //MUSE GEOMETRY META
//         MUSE::SurfaceMeta surfmeta;
//         surfmeta.read(JSONfilename);

//         deps = surfmeta.getCommands();
//     }
//     else if(loc == apps[1] && JSONfilename.find("volume") != std::string::npos)
//     {
//         //MUSE GEOMETRY META
//         MUSE::VolumeMeta volmeta;
//         volmeta.read(JSONfilename);

//         deps = volmeta.getCommands();
//     }
//     else if(loc == apps[2] && JSONfilename.find(key0) != std::string::npos)
//     {
//         //MUSE MANIPULATE META
//         MUSE::ManipulateMeta extrmeta;
//         extrmeta.read(JSONfilename);

//         deps = extrmeta.getCommands();
//     }
//     else if(loc == apps[2] && JSONfilename.find(key1) != std::string::npos)
//     {
//         //MUSE MANIPULATE META
//         MUSE::ManipulateMeta extrmeta;
//         extrmeta.read(JSONfilename);

//         deps = extrmeta.getCommands();
//     }
//     else if(loc == apps[2])
//     {
//         //MUSE MANIPULATE META
//         MUSE::ExtractionMeta extrmeta;
//         extrmeta.read(JSONfilename);

//         deps = extrmeta.getCommands();
//     }
//     else if(loc == apps[3])
//     {
//         //MUSE VARIO META
//         MUSE::VarioMeta variometa;
//         variometa.read(JSONfilename);

//         deps = variometa.getCommands();
//     }
//     else if(loc == apps[4] && JSONfilename.find("_sgs") == std::string::npos)
//     {
//         //MUSE COMPUTE META
//         MUSE::ComputeMeta computemeta;
//         computemeta.read(JSONfilename);

//         deps = computemeta.getCommands();
//     }
//     else if(loc == apps[4])
//     {
//         //MUSE DATA META
//         MUSE::Metadata datameta;
//         datameta.read(JSONfilename);

//         deps = datameta.getCommands();
//     }
//     return deps;
// }

// void getDeps_from_JSON_extended(const std::string &JSONfilename, std::vector<std::string> &deps, std::vector<std::string> &commands)
// {
//     std::vector<std::string> apps {"data", "geometry", "manipulate", "vario", "compute"};

//     std::string loc;
//     for(const std::string &name:apps)
//     {
//         if(JSONfilename.find(name) != std::string::npos)
//         {
//             loc = name;
//             break;
//         }
//     }

//     std::string key0 = "samples_";
//     std::string key1 = "geom_";

//     if(loc == apps[0])
//     {
//         //MUSE DATA META
//         MUSE::Metadata datameta;
//         datameta.read(JSONfilename);

//         deps = datameta.getDeps();
//         commands = datameta.getCommands();
//     }
//     else if(loc == apps[1] && JSONfilename.find("surf") != std::string::npos)
//     {
//         //MUSE GEOMETRY META
//         MUSE::SurfaceMeta surfmeta;
//         surfmeta.read(JSONfilename);

//         deps = surfmeta.getDeps();
//         commands = surfmeta.getCommands();
//     }
//     else if(loc == apps[1] && JSONfilename.find("volume") != std::string::npos)
//     {
//         //MUSE GEOMETRY META
//         MUSE::VolumeMeta volmeta;
//         volmeta.read(JSONfilename);

//         deps = volmeta.getDeps();
//         commands = volmeta.getCommands();
//     }
//     else if(loc == apps[2] && JSONfilename.find(key0) != std::string::npos)
//     {
//         //MUSE MANIPULATE META
//         MUSE::ManipulateMeta extrmeta;
//         extrmeta.read(JSONfilename);

//         deps = extrmeta.getDeps();
//         commands = extrmeta.getCommands();
//     }
//     else if(loc == apps[2] && JSONfilename.find(key1) != std::string::npos)
//     {
//         //MUSE MANIPULATE META
//         MUSE::ManipulateMeta extrmeta;
//         extrmeta.read(JSONfilename);

//         deps = extrmeta.getDeps();
//         commands = extrmeta.getCommands();
//     }
//     else if(loc == apps[2])
//     {
//         //MUSE MANIPULATE META
//         MUSE::ExtractionMeta extrmeta;
//         extrmeta.read(JSONfilename);

//         deps = extrmeta.getDeps();
//         commands = extrmeta.getCommands();
//     }
//     else if(loc == apps[3])
//     {
//         //MUSE VARIO META
//         MUSE::VarioMeta variometa;
//         variometa.read(JSONfilename);

//         deps = variometa.getDeps();
//         commands = variometa.getCommands();
//     }
//     else if(loc == apps[4] && JSONfilename.find("_sgs") == std::string::npos)
//     {
//         //MUSE COMPUTE META
//         MUSE::ComputeMeta computemeta;
//         computemeta.read(JSONfilename);

//         deps = computemeta.getDeps();
//         commands = computemeta.getCommands();
//     }
//     else if(loc == apps[4])
//     {
//         //MUSE DATA META
//         MUSE::Metadata datameta;
//         datameta.read(JSONfilename);

//         deps = datameta.getDeps();
//         commands = datameta.getCommands();
//     }
// }



