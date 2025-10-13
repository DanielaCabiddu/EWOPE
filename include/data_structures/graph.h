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

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <deque>

namespace EWOPE
{

// Data structure to store a graph edge
struct Edge {
    int src, dest;
};

// A class to represent a graph object
class Graph
{
public:
    // a vector of vectors to represent an adjacency list
    std::vector<std::vector<int>> adj_src2dest;
    std::vector<std::vector<int>> adj_dest2src;

    // Graph Constructor
    Graph(std::vector<Edge> const &edges, int n)
    {
        // resize the vector to hold `n` elements of type `vector<int>`
        adj_src2dest.resize(n);

        // add edges to the directed graph
        for (auto &edge: edges)
        {
            // insert at the end
            adj_src2dest[edge.src].push_back(edge.dest);
            adj_dest2src[edge.dest].push_back(edge.src);

            // uncomment the following code for undirected graph
            // adj_src2dest[edge.dest].push_back(edge.src);
        }
    }

    void printGraph(Graph const &graph, int n, std::deque<std::string> deps);
    void printGraph2(Graph const &graph, int n, std::deque<std::string> deps, std::deque<int> level);

    void printFormalism(Graph const &graph, int n, std::deque<std::string> &deps);


    void printGraph2(Graph const &graph, int n, std::deque<std::string> &deps);
    void printGraph2(Graph const &graph, int n, std::deque<std::string> &deps, std::deque<std::string> &com);

    void printGraph2_old(Graph const &graph, int n, std::deque<std::string> &deps, std::deque<std::string> &com);

    void printGraph2_old(Graph const &graph, int n, std::deque<std::string> &deps);
};

}

#ifndef STATIC_LIB
#include "graph.cpp"
#endif

#endif // GRAPH_H
