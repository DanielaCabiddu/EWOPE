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

#include <algorithm>
#include <climits>
#include <iostream>
#include <ostream>
#include <queue>
#include <string>
#include <vector>
#include <deque>
#include <set>
#include <map>

#include <fstream>

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
    std::map<int, std::string> node_map;
    std::map<int, std::string> command_map;

    // Graph Constructor
    //Graph(std::vector<Edge> const &edges, int n)
    Graph(std::vector<Edge> const &edges, const std::map<int, std::string> &deque_id2map, const std::map<int, std::string> &deque_id2com)
    {
        node_map = deque_id2map;
        command_map = deque_id2com;

        std::set<int> node_ids;

        for (auto &edge: edges)
        {
            node_ids.insert(edge.src);
            node_ids.insert(edge.dest);
        }

        //std::cout << *node_ids.rbegin() << std::endl;

        // resize the vector to hold `n` elements of type `vector<int>`
        adj_src2dest.resize(*node_ids.rbegin()+1);
        adj_dest2src.resize(*node_ids.rbegin()+1);

        std::vector<bool> is_pipe (*node_ids.rbegin()+1, false);

        for (int i=0; i < adj_dest2src.size(); i++)
            if (node_ids.find(i) == node_ids.end())
            {
                adj_dest2src.at(i).push_back(INT_MAX);
                adj_src2dest.at(i).push_back(INT_MAX);
            }

        // add edges to the directed graph
        for (auto &edge: edges)
        {
            // insert at the end
            adj_src2dest[edge.src].push_back(edge.dest);
            adj_dest2src[edge.dest].push_back(edge.src);
        }

        for (int i=0; i < adj_dest2src.size(); i++)
        {
            std::sort( adj_dest2src.at(i).begin(), adj_dest2src.at(i).end() );
            adj_dest2src.at(i).erase( std::unique( adj_dest2src.at(i).begin(), adj_dest2src.at(i).end() ), adj_dest2src.at(i).end() );

            std::sort( adj_src2dest.at(i).begin(), adj_src2dest.at(i).end() );
            adj_src2dest.at(i).erase( std::unique( adj_src2dest.at(i).begin(), adj_src2dest.at(i).end() ), adj_src2dest.at(i).end() );

        }

        node_formalism.resize(*node_ids.rbegin()+1, "");

        std::cout << std::endl;
        std::cout << "===============================================================" << std::endl;
        std::cout << std::endl;

        std::vector<int> inputs;

        //inizializzo il formalismo per i nodi sorgente
        //check bottom-up (sopra il nodo node_id)
        for (unsigned int i=0; i < adj_src2dest.size(); i++ )
        {
            if (!adj_src2dest.at(i).empty() && adj_src2dest.at(i).at(0) == INT_MAX)
                continue;

            if (adj_src2dest.at(i).empty())
            {
                inputs.push_back(i);
                node_formalism.at(i) = "[D" + std::to_string(inputs.size()) + "]";

                //std::cout << "Input node: " << i << " :: " << node_formalism.at(i) << std::endl;

            }
        }

        int counter_a = 0;

        //Ciclo sugli input
        for (unsigned int i=0; i < inputs.size(); i++ )
        {
            std::queue<int> queue; //creo una coda per ciclare sugli input
            queue.push(inputs.at(i));

            while (!queue.empty())
            {
                int node_id = queue.front(); //id input
                queue.pop();

                //estraggo le dipendenze top-down del node_id (al di sotto di node_id)
                const std::vector<int> depsnode = adj_dest2src[node_id];

                //controllo se non ci sono dipendenze: errore! vai avanti
                if (depsnode.empty())
                    continue;

                //Ciclo sulle dipendenze del node_id ed individuo le relazioni
                for (size_t j = 0; j < depsnode.size(); ++j)
                {
                    if (node_formalism.at(depsnode.at(j)).length() == 0)
                    {
                        if (j==0)
                            counter_a++;

                        node_formalism.at(depsnode.at(j)) = "[" + node_formalism.at(node_id) + "a" + std::to_string(counter_a) + "]";
                        queue.push(depsnode.at(j));

                        //std::cout << "Input node: " << depsnode.at(j) << " :: " << node_formalism.at(depsnode.at(j)) << std::endl;
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

                        //int count_k = 0;
                        for (int k : depsnode2)
                        {
                            data += node_formalism.at(k) + " ";

                            // count_k++;
                            // if(count_k == depsnode2.size()-1)
                            //     data += node_formalism.at(k);
                            // else
                            //     data += node_formalism.at(k)+" U ";
                        }

                        node_formalism.at(depsnode.at(j)) = "[" + data + suba;

                        //std::cout << "Input node: " << depsnode.at(j) << " :: " << node_formalism.at(depsnode.at(j)) << std::endl;
                    }
                }

                bool pipe = false;
                int counter_d = 1;

                for (size_t j = 0; j < depsnode.size(); ++j)
                {
                    if (depsnode.size() > 1 && is_pipe.at(depsnode.at(j)) == false)
                    {
                        node_formalism.at(depsnode.at(j)) = "[" + node_formalism.at(depsnode.at(j)) + "|" + std::to_string(counter_d++) + "]";
                        //std::cout << "Renamed Input node: " << depsnode.at(j) << " :: " << node_formalism.at(depsnode.at(j)) << std::endl;
                        pipe = true;

                        is_pipe.at(depsnode.at(j)) = true;
                    }
                }

                // if (pipe == true)
                //     counter_a--;
            }
        }

        std::cout << "INDEX_DATANODE ::::: NODE_FORMALISM" << std::endl;
        for (int i =0; i < node_formalism.size(); i++)
        {
            std::string s = node_formalism.at(i);
            if (s.length() > 0)
                std::cout << i << " ::::: " << s << std::endl;
        }
        std::cout << std::endl;

        std::cout << "ALGNODE ::::: COMMAND" << std::endl;
        for (int i =0; i < command_map.size(); i++)
        {
            if(!node_formalism.at(i).empty() && !command_map.at(i).empty())
            {
                //Cleaning string for print algorithm notation
                std::string alg="";
                if(node_formalism.at(i).find_last_of("a"))
                    alg = node_formalism.at(i).substr(node_formalism.at(i).find_last_of("a"), node_formalism.at(i).find_last_of("a")+1);
                if(node_formalism.at(i).find_last_of("]"))
                    alg = alg.substr(0, alg.find_last_of("]"));
                if(node_formalism.at(i).find_last_of("|"))
                    alg = alg.substr(0, alg.find_last_of("|"));

                if(node_formalism.at(i).find_last_of("]"))
                    alg = alg.substr(0, alg.find_last_of("]"));

                std::cout << alg << " ::::: " << command_map.at(i) << std::endl;
            }
        }

        exportToGraphviz(adj_src2dest,node_formalism, "test.dot");
    }

    void exportToGraphviz(const std::vector<std::vector<int>>& adj_src2dest,
                          const std::vector<std::string>& node_formalism,
                          const std::string& filename)
    {
        std::ofstream out(filename);
        out << "digraph G {\n";  // or "graph G {" for undirected graphs

        // define nodes
        for (size_t i = 0; i < node_formalism.size(); ++i) {
            if (node_formalism[i].length() > 0)
                out << "  " << i << " [label=\"" << node_formalism[i] << "\"];\n";
        }

        // define edges
        for (size_t i = 0; i < adj_src2dest.size(); ++i) {
            for (int dest : adj_src2dest[i]) {
                if (dest != INT_MAX && node_formalism[i].length() > 0 && node_formalism[dest].length() > 0)
                    out << "  " << i << " -> " << dest << ";\n";
            }
        }

        out << "}\n";
    }

    void printHistory (Graph const &graph, bool print_command = false);
};

}

#ifndef STATIC_LIB
#include "graph.cpp"
#endif

#endif // GRAPH_H
