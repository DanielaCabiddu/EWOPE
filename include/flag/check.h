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

#ifndef CHECK_H
#define CHECK_H

#include <vector>
#include <string>

#include "data_structures/data.h"

// Checks on string
bool is_number(const std::string &str);

bool is_double_pos  (const std::string &str);
bool is_double_neg  (const std::string &str);
bool is_integer_pos (const std::string &str);
bool is_integer_neg (const std::string &str);
bool is_negative    (const std::string &str);
bool is_positive    (const std::string &str);

bool getCheck       (char code, std::string &value);

int count_ndvalues  (const std::vector<std::string> &values);
int count_navalues  (const std::vector<std::string> &values);
int count_posvalues (const std::vector<std::string> &values);
int count_negvalues (const std::vector<std::string> &values);
int count_allowedsymbol (const std::vector<std::string> &values);
int count_empty     (const std::vector<std::string> &values);

//void DataSummary    (const EWOPE::Data &data);

// Check if numerical conversion is possible related to flag
//std::string num_conversion(const std::string &code);
//std::vector<double> getConversion (const std::vector<std::string> &variable, const std::string &flag, std::string negative_value, bool nd_value);


#ifndef STATIC_EWOPE
#include "check.cpp"
#endif

#endif // CHECK_H
