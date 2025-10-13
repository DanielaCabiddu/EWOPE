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

#include <iostream>
#include <ostream>
#include <queue>
#include <string>
#include <vector>
#include <deque>
#include <set>
#include <map>

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

    std::vector<std::string> node_formalism;

    // Graph Constructor
    Graph(std::vector<Edge> const &edges, int n)
    {
        std::set<int> node_ids;

        // resize the vector to hold `n` elements of type `vector<int>`
        adj_src2dest.resize(n);
        adj_dest2src.resize(n);

        // add edges to the directed graph
        for (auto &edge: edges)
        {
            // insert at the end
            adj_src2dest[edge.src].push_back(edge.dest);
            adj_dest2src[edge.dest].push_back(edge.src);

            node_ids.insert(edge.src);
            node_ids.insert(edge.dest);

            // uncomment the following code for undirected graph
            // adj_src2dest[edge.dest].push_back(edge.src);
        }

        node_formalism.resize(node_ids.size());

        std::cout << "====================================================================" << std::endl;

        std::vector<int> inputs;

        for (unsigned int i=0; i < adj_src2dest.size(); i++ )
        {
            if (adj_src2dest.at(i).empty())
            {
                inputs.push_back(i);
                node_formalism.at(i) = "[D" + std::to_string(inputs.size()) + "]";

                std::cout << "Input node: " << i << " :: " << node_formalism.at(i) << std::endl;

            }
        }

        int counter_a = 1;
        int counter_d = 1;

        for (unsigned int i=0; i < inputs.size(); i++ )
        {
            std::queue<int> queue;
            queue.push(inputs.at(i));

            while (!queue.empty())
            {
                int node_id = queue.front();
                queue.pop();

                const std::vector<int> depsnode = adj_dest2src[node_id];

                if (depsnode.empty())
                    continue;

                for (size_t j = 0; j < depsnode.size(); ++j)
                {
                    if (node_formalism.at(depsnode.at(j)).length() == 0)
                    {
                        if (depsnode.size() == 1)
                            counter_a++;

                        node_formalism.at(depsnode.at(j)) = "[" + node_formalism.at(node_id) + "a" + std::to_string(counter_a) + "]";

                        queue.push(depsnode.at(j));

                        std::cout << "Input node: " << j << " :: " << node_formalism.at(depsnode.at(j)) << std::endl;
                    }
                    else
                    {
                        std::vector<int> depsnode2 = adj_src2dest[depsnode.at(j)];

                        bool ready = true;

                        for (int k : depsnode2)
                        {
                            if (node_formalism.at(k).length() == 0)
                            {
                                ready = false;
                                break;
                            }
                        }

                        if (!ready)
                            continue;

                        std::string suba = node_formalism.at(depsnode.at(j)).substr(node_formalism.at(depsnode.at(j)).find_last_of("a"));
                        std::string data;

                        for (int k : depsnode2)
                        {
                            data += node_formalism.at(k);
                        }

                        node_formalism.at(depsnode.at(j)) = "[" + data + suba;

                        std::cout << "Input node: " << j << " :: " << node_formalism.at(depsnode.at(j)) << std::endl;
                    }
                }

                if (!adj_src2dest.at(node_id).empty() && depsnode.size() == 1)
                {
                    node_formalism.at(node_id) = "[" + node_formalism.at(node_id) + "|" + std::to_string(counter_d++) + "]";
                }
            }
        }

        std::cout << "====================================================================" << std::endl;

        for (std::string s : node_formalism)
            std::cout << s << std::endl;
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
