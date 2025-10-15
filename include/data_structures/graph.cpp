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

/***
 We thank https://www.techiedelight.com/graph-implementation-using-stl/ for providing the original code used in this file.
 We slightly modified it to suit the needs and purposes of the EWoPe project.
***/

#include "graph.h"

#include <iostream>

namespace EWOPE
{

void printHistory(Graph const &graph)
{
    std::string root = "WORKFLOW";
    std::cout << root << std::endl;

    int n = graph.node_map.size();

    int id = n-1;
    for ( auto it = graph.node_map.rbegin(); it != graph.node_map.rend(); ++it  )
    {
        std::string prefix = (id != 0) ? "|-- " : "|__ ";
        std::string string = prefix;

        id--;

        //std::vector<int> deps = graph.adj_dest2src[it->first]; //deps sotto al nodo
        std::vector<int> deps = graph.adj_src2dest[it->first]; //deps sopra al nodo
        if(!deps.empty())
        {
            int id_dep=0;
            for(int d : deps)
            {
                if(id_dep == deps.size())
                {
                    if(graph.node_map.find(d)->first)
                        string += graph.node_map.find(d)->second;
                }
                else
                {
                    if(id_dep == deps.size()-1)
                        string += graph.node_map.find(d)->second;
                    else
                        string += graph.node_map.find(d)->second + " + ";
                }
                id_dep++;
            }

        }
        string += " ---> ";
        string += it->second;

        if(!deps.empty())
            std::cout << string << std::endl;
    }
}

}

