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
#include <iomanip>
#include <unordered_map>
#include <unordered_set>

namespace EWOPE
{

// Function to print adjacency list representation of a graph
void printGraph(Graph const &graph, int n, std::deque<std::string> deps, std::deque<int> level)
{
    std::string root = "WORKFLOW";
    std::cout << root << std::endl;
    //std::cout << "|" << std::endl;

    std::string prefix = "├── ";
    std::string string;
    //for (int i = 0; i < n; i++)
    for (int i = n-1; i >= 0; i--)
    {
        int prev = i+1;

        if (i!=n-1 && graph.adj_src2dest[i].size() == 0 && level.at(i) == level.at(prev))
        {
            string = "|   " + deps.at(i);
        }
        else if (i==n-1 && graph.adj_src2dest[i].size() == 0)
        {
            string = prefix + deps.at(i);
        }
        else if (graph.adj_src2dest[i].size() == 0)
        {
            string = prefix + deps.at(i);
        }
        else
            string = deps.at(i) + " ——> ";

        std::cout << string ;

        // print the current vertex number
//        std::cout << deps.at(i) << " ——> ";
//        //cout << i << " ——> ";


        // print all neighboring vertices of a vertex `i`
        for (int v: graph.adj_src2dest[i])
        {
            std::cout << deps.at(v) << " ";
        }
        std::cout << std::endl;
        //std::cout << "|" << std::endl;
    }
    std::cout << "└── " << std::endl;
}

void printGraph2(Graph const &graph, int n, std::deque<std::string> deps, std::deque<int> level)
{
    std::string root = "WORKFLOW";
    std::cout << root << std::endl;
    std::string prefix = "├── ";
    //std::cout << prefix << std::endl;

    std::string string;
    for (int i = n-1; i >= 0; i--)
    {
        if(i != 0)
        {
            // print all neighboring vertices of a vertex `i`
            if(graph.adj_src2dest[i].size() > 0)
            {
                for (int v=0; v< graph.adj_src2dest[i].size(); v++)
                {
                    if(v >= 0 && graph.adj_src2dest[i].size() > 1 && v != graph.adj_src2dest[i].size()-1)
                    {
                        std::cout << prefix + deps.at(graph.adj_src2dest[i].at(v)) << " + ";
                    }
                    else if(v==0 || v == graph.adj_src2dest[i].size()-1)
                    {
                        std::cout << prefix + deps.at(graph.adj_src2dest[i].at(v));
                    }
                    else
                    {
                        if(graph.adj_src2dest[i].size() > 1)
                            std::cout << deps.at(graph.adj_src2dest[i].at(v)) << " + " ;
                        else
                            std::cout << deps.at(graph.adj_src2dest[i].at(v));
                    }
                }
                std::cout << " ——> " << deps.at(i) << std::endl;

            }
//            else
//                std::cout << prefix + " INPUT ";



//            if(graph.adj_src2dest[i].size() != 0)
//                std::cout << " ——> " << deps.at(i) << std::endl;
//            else
//                std::cout << " INPUT " <<  std::endl;
            //std::cout << std::endl;
        }
        else // se i==0 chiudo └──
        {
            // print all neighboring vertices of a vertex `i`
            for (int v: graph.adj_src2dest[i])
            {
                if(v == graph.adj_src2dest[i].size())
                    std::cout << "└── " << deps.at(v);
                else
                {
                    if(graph.adj_src2dest[i].size() > 1)
                        std::cout << "└── " << deps.at(v) << " + " ;
                    else
                        std::cout << "└── " << deps.at(v);
                }
            }
            if(graph.adj_src2dest[i].size() != 0)
                std::cout << " ——> " << deps.at(i) << std::endl;
            std::cout << std::endl;
        }
    }

}



void printGraph2(Graph const &graph, int n, std::deque<std::string> &deps)
{
    std::string root = "WORKFLOW";
    std::cout << root << std::endl;
    //std::cout << prefix << std::endl;

    std::unordered_set<std::string> printed;  // per evitare duplicati

    for (int i = n-1; i >= 0; i--)
    {
        std::string prefix = (i != 0) ? "|-- " : "|__ ";
        std::string string = prefix;

        // print all neighboring vertices of a vertex `i`
        if(graph.adj_src2dest[i].size() > 0)
        {
            for (size_t v=0; v< graph.adj_src2dest[i].size(); v++)
            {
                if(graph.adj_src2dest[i].size() == 1)
                    string += deps.at(graph.adj_src2dest[i].at(v));
                else
                {
                    if(v == graph.adj_src2dest[i].size()-1)
                        string += deps.at(graph.adj_src2dest[i].at(v));
                    else
                        string += deps.at(graph.adj_src2dest[i].at(v)) + " + ";
                }
            }

            if(string.find("in/") != std::string::npos)
                std::cout << string << " --> " << deps.at(i) << std::endl;
            else
                std::cout << string << " --> " << deps.at(i) << std::endl;
        }
    }
}


void printFormalism(Graph const &graph, int n, std::deque<std::string> &deps)
{
    std::string root = "FORMALISM";
    std::cout << root << std::endl;

    std::vector<std::string> formal_in(n);  // Per tracciare le trasformazioni [D1a1], ecc.
    std::vector<std::string> formal_out(n);
    std::vector<std::string> formal_alg(n);
    std::unordered_map<int, int> a_counters; // Contatori a1, a2, a3... per ciascun nodo

    // Costruisci anche la lista inversa (per capire 1:many)
    std::vector<std::vector<int>> revadj_src2dest(n);
    for (int i = 0; i < n; ++i)
        for (auto dep : graph.adj_src2dest[i])
            revadj_src2dest[dep].push_back(i);

    int count_inputnode = 0;
    int count_algnode = 0;
    for (int i = n-1; i >= 0; i--)
    {
        if(graph.adj_src2dest[i].empty()) //se non ha dipendenze, inizializza come dato sorgente
        {
            count_inputnode++;
            formal_in[i] = "[D" + std::to_string(count_inputnode) + "]";
        }
    }
    std::cout << "=== Number of input node in the graph: " << count_inputnode << std::endl;

    for (int i = n-2; i >= 0; i--)
    {
        std::string source = "[D";
        std::string output = "";
        const auto &depsnode = graph.adj_src2dest[i];
        const auto &outs = revadj_src2dest[i];

        //relazione 1:1
        if (depsnode.size()==1)
        {
            if(formal_in[i].empty())
            {
                std::cout << "VUOTOOOO" << std::endl;
                // Nodo senza output
                // source += std::to_string(i+1) + "]";
                // formal_in[depsnode[i]] = source;
                source = formal_in[depsnode[0]];
                formal_in[i] = source;
            }
            // else
            // {
            //     source += std::to_string(i+1) + "]";
            // }

            source = formal_in[i];
            formal_alg[i] = "a" + std::to_string(count_algnode+1);
            count_algnode++;

            output = source.substr(0, source.size() - 1) + formal_alg[i] + "]";
            formal_out[i] = output;
            continue;
        }
        //relazione many:1
        else if (depsnode.size()>1)
        {
            source.clear();
            if (formal_in[i].empty())
            {
                for (size_t j = 0; j < depsnode.size(); ++j)
                {
                    if(j == depsnode.size()-1)
                        source += formal_in[depsnode[j]];
                    else
                        source += formal_in[depsnode[j]] + " U ";
                }
            }
            formal_in[i] = source;
            formal_alg[i] = "a" + std::to_string(count_algnode+1);
            count_algnode++;

            output = "[" + source + "]"+formal_alg[i];
            formal_out[i] = output;
        }
        // // 🟣 Caso 1:many
        // else if (depsnode.size() == 1 && outs.size() > 1)
        // {
        //     source = formal_in[depsnode[0]];
        //     formal_alg[i] = "a" + std::to_string(i + 1);
        //     output = "[" + source + "]" + formal_alg[i] + " → {";

        //     for (size_t j = 0; j < outs.size(); ++j)
        //     {
        //         output += "D" + std::to_string(outs[j] + 1);
        //         if (j < outs.size() - 1)
        //             output += ", ";
        //     }
        //     output += "}";
        //     formal_out[i] = output;
        // }
    }


    for(unsigned int i=0;i<formal_in.size();i++)
    {
        if(!formal_in[i].empty() && !formal_out[i].empty())
            std::cout << formal_in[i] << " --> " << formal_out[i] << std::endl;
        else if(!formal_in[i].empty() && formal_out[i].empty())
            std::cout << formal_in[i] << std::endl;
    }

    // // Prima passata: 1:1 e 1:many (chi parte da un nodo input)
    // //for (int i = 0; i < n; ++i)
    // for (int i = n-1; i >= 0; i--)
    // {
    //     std::string source = "[D";
    //     const auto &depsnode = graph.adj_src2dest[i];

    //     //relazione 1:1
    //     if (depsnode.empty())
    //     {
    //         // Nodo senza output
    //         source += "]";
    //         formal_output.push_back(source);
    //         continue;
    //     }

    //     if (depsnode.size() == 1)
    //     {
    //         // 1:1
    //         int a_index = ++a_counters[i];
    //         std::string transformed = source.substr(0, source.size() - 1) + "a" + std::to_string(a_index) + "]";
    //         form_in[depsnode[0]] = transformed;

    //         formal_output.push_back(source + " -> " + transformed);
    //     }
    //     else
    //     {
    //         // 1:many
    //         int a_index = ++a_counters[i];
    //         std::vector<std::string> branches;

    //         for (size_t j = 0; j < depsnode.size(); ++j)
    //         {
    //             std::string branch = source.substr(0, source.size() - 1) + "a" + std::to_string(a_index) + "|" + std::to_string(j + 1) + "]";
    //             form_in[depsnode[j]] = branch;
    //             branches.push_back(branch);
    //         }

    //         std::string line = source + " -> ";
    //         for (size_t j = 0; j < branches.size(); ++j)
    //         {
    //             line += branches[j];
    //             if (j != branches.size() - 1)
    //                 line += ", ";
    //         }

    //         formal_output.push_back(line);
    //     }
    // }

    // // Seconda passata: many:1 (nodo con più input)
    // //for (int i = 0; i < n; ++i)
    // for (int i = n-1; i >= 0; i--)
    // {
    //     const auto &inputs = graph.adj_src2dest[i];
    //     if (inputs.size() <= 1) continue;

    //     std::string target = "[D" + std::to_string(i + 1) + "]";
    //     std::string line = target + " = ";

    //     for (size_t j = 0; j < inputs.size(); ++j)
    //     {
    //         int input_node = inputs[j];

    //         // Se non è ancora stato trasformato, creiamo nome standard
    //         if (form_in[i].empty())
    //         {
    //             int a_index = ++a_counters[input_node];
    //             form_in[input_node] = "[D" + std::to_string(input_node + 1) + "a" + std::to_string(a_index) + "]";
    //         }

    //         std::string dep = form_in[input_node];
    //         line += dep;
    //         if (j != inputs.size() - 1)
    //             line += " + ";
    //     }

    //     formal_output.push_back(line);
    // }

    // // Stampa in ordine inverso (dagli input verso i nodi calcolati)
    // for (auto it = formal_in.begin(); it != formal_in.end(); ++it)
    //     std::cout << *it << " --> ";

    // for (auto it = formal_out.begin(); it != formal_out.end(); ++it)
    //     std::cout << *it << std::endl;
}

void printFormalism_old(Graph const &graph, int n, std::deque<std::string> &deps)
{
    std::string root = "FORMALISM";
    std::cout << root << std::endl;

    std::vector<std::string> nodeNames(n);
    int transID=1;

    // Costruisci i nomi base dei nodi
    for (int i = 0; i < n; ++i)
        nodeNames[i] = "[D" + std::to_string(i+1) + "]";

    for (int i = 0; i < n; ++i)
    {
        const auto &depsList = graph.adj_src2dest[i];

        if (depsList.empty())
        {
            // Nodo iniziale (no input)
            std::cout << nodeNames[i] << std::endl;
        }
        else if (depsList.size() == 1)
        {
            // 1:1
            std::string source = nodeNames[depsList[0]];
            std::string target = source.substr(0, source.size() - 1) + "a" + std::to_string(transID++) + "]";
            std::cout << source << " -> " << target << std::endl;
            nodeNames[i] = target;
        }
        else
        {
            // many:1
            std::string target = "[D" + std::to_string(i+1) + "]";
            std::cout << target << " = ";

            for (size_t j = 0; j < depsList.size(); ++j)
            {
                int dep = depsList[j];
                std::string source = nodeNames[dep];
                std::string transformed = source.substr(0, source.size() - 1) + "a" + std::to_string(transID++) + "]";
                std::cout << transformed;

                if (j != depsList.size() - 1)
                    std::cout << " + ";
            }
            std::cout << std::endl;
        }

        // Check se ha più output (1:many)
        int out_degree = 0;
        for (int j = 0; j < n; ++j)
        {
            for (int v : graph.adj_src2dest[j])
            {
                if (v == i) out_degree++;
            }
        }

        if (out_degree > 1)
        {
            std::cout << nodeNames[i] << " -> ";
            for (int k = 1; k <= out_degree; ++k)
            {
                std::cout << nodeNames[i].substr(0, nodeNames[i].size() - 1) + "|" + std::to_string(k) + "]";
                if (k != out_degree) std::cout << ", ";
            }
            std::cout << std::endl;
        }
    }

    // int n_outnode = 0; // per contare i nodi output
    // std::string curr, succ;

    // std::string prev = "[D" + std::to_string(n_outnode+1) + "]";

    // std::string prefix = ((n-1) != 0) ? "|-- " : "|__ ";
    // std::string string = prefix + prev + " --> ";
    // form_in[n-1] = prev;
    // curr = prev;
    // std::cout << string << std::endl;

    // for (int i = n-2; i >= 0; i--)
    // {
    //     prefix = (i != 0) ? "|-- " : "|__ ";

    //     //sono in un nodo output
    //     //verifico il numero di dipendenze
    //     if(graph.adj_src2dest[i].empty())
    //     {
    //         //no dipendenze
    //     }
    //     else if(graph.adj_src2dest[i].size()==1) //1:1
    //     {
    //         //curr ="[D" + std::to_string(n_outnode+1) + "a"+std::to_string(n_outnode+1) +"]";
    //         curr = prev + "a";
    //         string += curr;
    //     }
    //     else if(graph.adj_src2dest[i].size()>1) //many:1
    //     {
    //         //somma dei nodi
    //         for (size_t v=0; v< graph.adj_src2dest[i].size(); v++)
    //         {
    //             curr = prev + "a";

    //             if(v == graph.adj_src2dest[i].size()-1)
    //                 string += curr;
    //             else
    //                 string += curr + " + ";

    //         }
    //     }
    //     std::cout << string << std::endl;
    //     prev = curr;
    // }

}


void printGraph2(Graph const &graph, int n, std::deque<std::string> &deps, std::deque<std::string> &com)
{
    std::string root = "WORKFLOW";
    std::cout << root << std::endl;
    //std::cout << prefix << std::endl;

    for (int i = n-1; i >= 0; i--)
    {
        std::string prefix = (i != 0) ? " |-- " : " |__ ";
        std::string string = prefix;

        // print all neighboring vertices of a vertex `i`
        if(graph.adj_src2dest[i].size() > 0)
        {
            for (size_t v=0; v< graph.adj_src2dest[i].size(); v++)
            {
                if(graph.adj_src2dest[i].size() == 1)
                    string += deps.at(graph.adj_src2dest[i].at(v));
                else
                {
                    if(v == graph.adj_src2dest[i].size()-1)
                        string += deps.at(graph.adj_src2dest[i].at(v));
                    else
                        string += deps.at(graph.adj_src2dest[i].at(v)) + " + ";
                }
            }

            if(string.find("in/") != std::string::npos)
                std::cout << string << " --> " << deps.at(i) << std::endl;
            else
                std::cout << string << " --> " << deps.at(i) << std::endl;

            std::cout << std::setfill(' ') << std::right << std::setw(string.length()+3) << " --> " << com.at(i) << std::endl;
        }
    }
}


void printGraph2_old(Graph const &graph, int n, std::deque<std::string> &deps)
{
    std::string root = "WORKFLOW";
    std::cout << root << std::endl;
    std::string prefix;
    //std::cout << prefix << std::endl;

    for (int i = n-1; i >= 0; i--)
    {
        std::string string;
        if(i != 0)
        {
            prefix = " |-- ";

            // print all neighboring vertices of a vertex `i`
            if(graph.adj_src2dest[i].size() > 0)
            {
                for (size_t v=0; v< graph.adj_src2dest[i].size(); v++)
                {
                    if(v >= 0 && graph.adj_src2dest[i].size() > 1) // && v != graph.adj_src2dest[i].size()-1)
                    {
                        if(v == graph.adj_src2dest[i].size()-1)
                            string += prefix + deps.at(graph.adj_src2dest[i].at(v));
                        else
                            string += prefix + deps.at(graph.adj_src2dest[i].at(v)) + " + ";
                        //std::cout << prefix + deps.at(graph.adj_src2dest[i].at(v)) << " + ";
                    }
                    else if(v==0 || v == graph.adj_src2dest[i].size()-1)
                    {
                        //string = deps.at(graph.adj_src2dest[i].at(v));
                        string = prefix + deps.at(graph.adj_src2dest[i].at(v));
                        //std::cout << prefix + deps.at(graph.adj_src2dest[i].at(v));
                    }
                    else
                    {
                        if(graph.adj_src2dest[i].size() > 1)
                            string += deps.at(graph.adj_src2dest[i].at(v)) + " + " ;
                        //std::cout << deps.at(graph.adj_src2dest[i].at(v)) << " + " ;
                        else
                            string = deps.at(graph.adj_src2dest[i].at(v));
                        //std::cout << deps.at(graph.adj_src2dest[i].at(v));
                    }
                }
                if(string.find("in/") != std::string::npos)
                    std::cout << "\e[1m" << string << "\e[0m" << " ——> " << deps.at(i) << std::endl;
                else
                    std::cout << string << " ——> " << deps.at(i) << std::endl;
            }
        }
        else // se i==0 chiudo └──
        {
            prefix = "└── ";

            if(graph.adj_src2dest[i].size() > 0)
            {
                // print all neighboring vertices of a vertex `i`
                for (size_t v: graph.adj_src2dest[i])
                {
                    if(v == graph.adj_src2dest[i].size())
                        string = prefix + deps.at(v);
                    //std::cout << "└── " << deps.at(v);
                    else
                    {
                        if(graph.adj_src2dest[i].size() > 1)
                            string = prefix + deps.at(v) + " + ";
                        //std::cout << "└── " << deps.at(v) << " + " ;
                        else
                            string = prefix + deps.at(v);
                        //std::cout << "└── " << deps.at(v);
                    }
                }
                if(string.find("in/") != std::string::npos)
                    std::cout << "\e[1m" << string << "\e[0m" << " ——> " << deps.at(i) << std::endl;
                else
                    std::cout << string << " ——> " << deps.at(i) << std::endl;
            }

            std::cout << std::endl;
        }
    }

}


void printGraph2_old(Graph const &graph, int n, std::deque<std::string> &deps, std::deque<std::string> &com)
{
    std::string root = "WORKFLOW";
    std::cout << root << std::endl;
    std::string prefix;
    //std::cout << prefix << std::endl;

    for (int i = n-1; i >= 0; i--)
    {
        std::string string;
        if(i != 0)
        {
            prefix = "├── ";

            // print all neighboring vertices of a vertex `i`
            if(graph.adj_src2dest[i].size() > 0)
            {
                for (size_t v=0; v< graph.adj_src2dest[i].size(); v++)
                {
                    if(v >= 0 && graph.adj_src2dest[i].size() > 1 && v != graph.adj_src2dest[i].size()-1)
                    {
                        string = prefix + deps.at(graph.adj_src2dest[i].at(v)) + " + ";
                        //std::cout << prefix + deps.at(graph.adj_src2dest[i].at(v)) << " + ";
                    }
                    else if(v==0 || v == graph.adj_src2dest[i].size()-1)
                    {
                        string = prefix + deps.at(graph.adj_src2dest[i].at(v));
                        //std::cout << prefix + deps.at(graph.adj_src2dest[i].at(v));
                    }
                    else
                    {
                        if(graph.adj_src2dest[i].size() > 1)
                            string = deps.at(graph.adj_src2dest[i].at(v)) + " + " ;
                            //std::cout << deps.at(graph.adj_src2dest[i].at(v)) << " + " ;
                        else
                            string = deps.at(graph.adj_src2dest[i].at(v));
                            //std::cout << deps.at(graph.adj_src2dest[i].at(v));
                    }
                }
                if(string.find("in/") != std::string::npos)
                    std::cout << "\e[1m" << string << "\e[0m" << " ——> " << deps.at(i) << std::endl;
                else
                    std::cout << string << " ——> " << deps.at(i) << std::endl;
                std::cout << std::setfill(' ') << std::right << std::setw(string.length()+3) << " ——> " << com.at(i) << std::endl;
            }
        }
        else // se i==0 chiudo └──
        {
            prefix = "└── ";

            if(graph.adj_src2dest[i].size() > 0)
            {
                // print all neighboring vertices of a vertex `i`
                for (size_t v: graph.adj_src2dest[i])
                {
                    if(v == graph.adj_src2dest[i].size())
                        string = prefix + deps.at(v);
                        //std::cout << "└── " << deps.at(v);
                    else
                    {
                        if(graph.adj_src2dest[i].size() > 1)
                            string = prefix + deps.at(v) + " + ";
                            //std::cout << "└── " << deps.at(v) << " + " ;
                        else
                            string = prefix + deps.at(v);
                            //std::cout << "└── " << deps.at(v);
                    }
                }
                if(string.find("in/") != std::string::npos)
                    std::cout << "\e[1m" << string << "\e[0m" << " ——> " << deps.at(i) << std::endl;
                else
                    std::cout << string << " ——> " << deps.at(i) << std::endl;
                std::cout << std::setfill(' ') << std::right << std::setw(string.length()+3) << " ——> " << com.at(i) << std::endl;
            }

            std::cout << std::endl;
        }
    }

}

}


//class Node {
// public:
//    Node(std::string val) {
//        this->val = val;
//    }
//    std::vector<Node*> _prev;
//    std::vector<Node*> _children;
//    std::string val;

//void printSubtree(const std::string &prefix)
//{
//    using std::cout;
//    using std::endl;

//    if (_children.empty())
//        return;
//    cout << prefix;

//    size_t n_children = _children.size();
//    cout << (n_children > 1 ? "├── " : "");

//    for (size_t i = 0; i < n_children; ++i) {
//        Node *c = _children[i];
//        if (i < n_children - 1) {
//            if (i > 0) { // added fix
//                cout << prefix<< "├── "; // added fix
//            } // added fix
//            bool printStrand = n_children > 1 && !c->_children.empty();
//            std::string newPrefix = prefix + (printStrand ? "│\t" : "\t");
//            std::cout << c->val << "\n";
//            c->printSubtree(newPrefix);
//        } else {
//            cout << (n_children > 1 ? prefix : "") << "└── ";
//            std::cout << c->val << "\n";
//            c->printSubtree(prefix + "\t");
//        }
//    }
//}

//    void printTree() {
//        using std::cout;
//        std::cout << val << "\n";
//        printSubtree("");
//        cout << "\n";
//    }
//};
