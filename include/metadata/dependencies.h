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

#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

std::vector<std::string> get_from_JSON (const std::string &JSONfilename, const std::string &search);

// bool findDeps_from_JSON (const std::string &JSONfilename);
// std::vector<std::string> getDeps_from_JSON  (const std::string &JSONfilename);
// std::vector<std::string> getCom_from_JSON   (const std::string &JSONfilename);
// void getDeps_from_JSON_extended (const std::string &JSONfilename, std::vector<std::string> &deps, std::vector<std::string> &commands);


#ifndef STATIC_MUSELIB
#include "dependencies.cpp"
#endif

#endif // DEPENDENCIES_H
