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

#ifndef FLAG_H
#define FLAG_H

#include <string>
#include <vector>

namespace EWOPE
{
    struct Flag;
}

struct EWOPE::Flag
{
    std::string nameFlag;
    char charFlag;
    bool activeFlag;
    bool check;         //memorizza se per quel flag il check è stato superato
};


// Management of flags
EWOPE::Flag setFlag      (std::string name, char code, bool is_active = false);
void flagsTable         (std::vector<EWOPE::Flag> &table); // Definition of flags table (default)
void restoreTable       (std::vector<EWOPE::Flag> &table); // Restore default activeFlag in table
//void flagActivation     (std::vector<EWOPE::Flag> &table, const std::string &str_flag);
void flagActivation     (std::vector<EWOPE::Flag> &table, const std::string &str_flag);
int count_activeFlag    (std::vector<EWOPE::Flag> &table);
int count_passedCheck   (std::vector<EWOPE::Flag> &table);


// Check on vector
bool checkString        (const std::vector<std::string> &values);
bool checkReal          (const std::vector<std::string> &values);

bool checkPositive      (const std::vector<std::string> &values);
bool checkNegative      (const std::vector<std::string> &values);

bool checkCompositional (const std::vector<std::string> &values, const double &scale_factor, const double &inf = 0.0, const double &sup = 1.0);
//DA MODIFICARE: + coefficiente di scala in funzione dell'unità di misura


bool checkBounded       (const std::vector<std::string> &values, const double &inf, const double &sup);
bool checkProbability   (const std::vector<std::string> &values, const double &inf = 0.0, const double &sup = 1.0);
bool checkDepth         (const std::vector<std::string> &values);
bool checkAbsHeight     (const std::vector<std::string> &values);
bool checkSoft          (const std::vector<std::string> &values);

void getPreliminaryCheck (char code, std::vector<std::string> &values, bool &check, const double &scale_factor, const double &inf, const double &sup);


#ifndef STATIC_LIB
#include "flag.cpp"
#endif

#endif // FLAG_H
