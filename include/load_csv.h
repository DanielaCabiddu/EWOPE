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

#ifndef _LOAD_CSV_H
#define _LOAD_CSV_H

#include <string>
#include <vector>

void read_csv                   (const std::string filename, char delimiter, std::vector<std::vector<std::string>> &matrix);
void read_csv_with_header       (const std::string filename,
                                   int nrows_header,
                                   std::vector<std::vector<std::string>> &matrix_header,
                                   std::vector<std::vector<std::string>> &matrix_data,
                                   char delimiter = ';');

std::string string_printable    (const std::string &word);
size_t nchars_printable(const std::string &word);

std::string search_column_csv   (const std::string filename, int n_column, char delimiter = ';');

std::vector<std::string> extracting_kcolumn (const std::vector<std::vector<std::string>> &matrix, const int &k);
std::vector<std::vector<std::string>> extracting_kmatrix (const std::vector<std::vector<std::string>> &matrix, const int &k);
std::vector<std::string> extracting_krow (const std::vector<std::vector<std::string>> &matrix, const int &k);

void save_data                  (const std::string filename, std::vector<std::string> &values);

void count_whitespace           (const std::string &str);
bool searching_special_chars    (const std::string &string, char c);
int pos_special_chars           (const std::string &string, char *c);

void read_header_csv (const std::string filename, int nrows_header, std::vector<std::vector<std::string>> &matrix_header, char delimiter);
bool equal_cell (std::string cell0, std::string cell1);
bool equal_column (std::vector<std::string> col0,std::vector<std::string> col1);
std::vector<bool> matrix_compare (const std::vector<std::vector<std::string>> &matrix0, const std::vector<std::vector<std::string>> &matrix1);
std::vector<std::pair<int, bool>> matrix_compare1 (const std::vector<std::vector<std::string>> &matrix0, const std::vector<std::vector<std::string>> &matrix1);

#ifndef STATIC_EWOPE
#include "load_csv.cpp"
#endif

#endif // LOAD_CSV_H
