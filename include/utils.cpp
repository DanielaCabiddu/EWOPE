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

#include "utils.h"

#include <algorithm>
#include <sstream>

#include <stdlib.h>

//for filesystem
#ifdef __APPLE__
    #include <filesystem>
    using namespace std::__fs;
#else
    //#include <experimental/filesystem>
    #include <filesystem>
    using namespace std;
#endif

#ifdef WIN32
    const char path_sep = '\\';
#else
    const char path_sep = '/';
#endif

inline
std::vector<std::string> split_string (const std::string &str, char delimiter)
{
    std::vector<std::string> v;
    std::stringstream ss(str);

    while (ss.good())
    {
        std::string substr;
        getline(ss, substr, delimiter);
        v.push_back(substr);
    }
    return v;
}

inline
std::pair<std::string,std::string> split_string_pair (const std::string &str, char delimiter)
{
    std::pair<std::string,std::string> v;
    if(str.find(delimiter) != std::string::npos)
    {
        v.first = str.substr(0, str.find_last_of(delimiter));
        v.second = str.substr(str.find_last_of(delimiter)+1, str.length());
    }
    return v;
}

inline
std::string get_path (const std::string &complete_path)
{
    std::string path;
    if(complete_path.find(path_sep) != std::string::npos)
        path = complete_path.substr(0, complete_path.find_last_of(path_sep));
    return path;
}

inline
std::string get_filename (const std::string &path)
{
    std::string filename;
    if(path.find(path_sep) != std::string::npos)
        filename = path.substr(path.find_last_of(path_sep)+1, path.length());
    return filename;
}

inline
std::string get_basename (const std::string &name)
{
    std::string basename;
    if(name.find(".") != std::string::npos)
        basename = name.substr(0, name.find_last_of("."));
    return basename;
}

inline
std::string get_extension (const std::string &name)
{
    std::string extension;
    if(name.find(".") != std::string::npos)
        extension = name.substr(name.find_last_of("."), name.length());
    return extension;
}

inline
bool find_char (const std::string &string, const char &c)
{
    if(string.find(c) != std::string::npos)
        return true;
    else
        return false;
}

inline
std::vector<std::string> get_directories(const std::string &project_dir)
{
    std::vector<std::string> list;
    for(auto& p : filesystem::directory_iterator(project_dir))
        #ifdef __APPLE__
        if (p.is_directory())
        #else
        if (filesystem::is_directory(p))
        #endif
            list.push_back(p.path().string());

    return list;
}

inline
std::vector<std::string> get_recursive_directories (const std::string &project_dir)
{
    std::vector<std::string> list;
    for(auto& p : filesystem::recursive_directory_iterator(project_dir))
        #ifdef __APPLE__
        if (p.is_directory())
        #else
        if (filesystem::is_directory(p))
        #endif
            list.push_back(p.path().string());

    return list;
}

inline
std::vector<std::string> get_files (const std::string &project_dir)
{
    std::vector<std::string> list;
    for(auto& p : filesystem::directory_iterator(project_dir))
        list.push_back(p.path().string());

    return list;
}

inline
std::vector<std::string> get_files (const std::string &project_dir, const std::string &ext, bool alphab_sort)
{
    std::vector<std::string> list;

    for(auto& p : filesystem::directory_iterator(project_dir))
    {
        std::string path = p.path().string();
//        std::string filename = path.substr(path.find_last_of("/")+1, path.length());

//        std::string extname;
//        if(filename.find(".") != std::string::npos)
//            extname = filename.substr(filename.find_last_of("."), filename.length());

//        if(extname.compare(ext) == 0)
//            list.push_back(p.path());

        if(get_extension(path).compare(ext) == 0)
            list.push_back(p.path().string());
    }
    if(alphab_sort == true)
        std::sort(list.begin(), list.end());

    return list;
}

inline
std::vector<std::string> get_vectorfiles (const std::string &project_dir)
{
    std::vector<std::string> list;
    for(auto& p : filesystem::directory_iterator(project_dir))
    {
        std::string path = p.path().string();
        std::string filename = path.substr(path.find_last_of("/")+1, path.length());

        std::string extname;
        if(filename.find(".") != std::string::npos)
            extname = filename.substr(filename.find_last_of("."), filename.length());

        if(extname.compare(".shp") == 0 || extname.compare(".gpkg") == 0)
            list.push_back(p.path().string());
    }

    return list;
}

inline
std::vector<std::string> get_rasterfiles (const std::string &project_dir)
{
    std::vector<std::string> list;
    for(auto& p : filesystem::directory_iterator(project_dir))
    {
        std::string path = p.path().string();
        std::string filename = path.substr(path.find_last_of("/")+1, path.length());

        std::string extname;
        if(filename.find(".") != std::string::npos)
            extname = filename.substr(filename.find_last_of("."), filename.length());

        if(extname.compare(".asc") == 0 || extname.compare(".gpkg") == 0)
            list.push_back(p.path().string());
    }

    return list;
}

inline
std::vector<std::string> get_shapefiles (const std::string &project_dir)
{
    std::vector<std::string> list;
    for(auto& p : filesystem::directory_iterator(project_dir))
    {
        std::string path = p.path().string();
        std::string filename = path.substr(path.find_last_of("/")+1, path.length());

        std::string extname;
        if(filename.find(".") != std::string::npos)
            extname = filename.substr(filename.find_last_of("."), filename.length());

        if(extname.compare(".shp") == 0)
            list.push_back(p.path().string());
    }

    return list;
}

inline
std::vector<std::string> get_xyzfiles (const std::string &project_dir)
{
    std::vector<std::string> list;
    for(auto& p : filesystem::directory_iterator(project_dir))
    {
        std::string path = p.path().string();
        std::string filename = path.substr(path.find_last_of("/")+1, path.length());

        std::string extname;
        if(filename.find(".") != std::string::npos)
            extname = filename.substr(filename.find_last_of("."), filename.length());

        if(extname.compare(".dat") == 0 || extname.compare(".xyz") == 0 || extname.compare(".txt") == 0 || extname.compare(".csv") == 0)
            list.push_back(p.path().string());
    }

    return list;
}

inline
std::vector<std::string> get_meshfiles (const std::string &project_dir)
{
    std::vector<std::string> list;
    for(auto& p : filesystem::directory_iterator(project_dir))
    {
        std::string path = p.path().string();
        std::string filename = path.substr(path.find_last_of("/")+1, path.length());

        std::string extname;
        if(filename.find(".") != std::string::npos)
            extname = filename.substr(filename.find_last_of("."), filename.length());

        if(extname.compare(".mesh") == 0 || extname.compare(".off") == 0)
            list.push_back(p.path().string());
    }

    return list;
}

inline
bool check_folder_name (const std::string new_name, std::string project_folder)
{
    bool equal_name = false;

    //lista cartelle a tutti i livelli
    std::vector<std::string> dirs = get_directories(project_folder);

    for(size_t i=0; i< dirs.size(); i++)
    {
        //std::cout << "Dir: " << dirs.at(i) << std::endl;
        std::string existed_name = dirs.at(i).substr(dirs.at(i).find_last_of(path_sep)+1, dirs.at(i).length());
        std::string basename = existed_name.substr(0, existed_name.find_last_of("."));

        if(new_name.compare(basename) == 0)
        {
            equal_name = true;
            break;
        }
    }
    return equal_name;
}

inline
bool check_filename (const std::string new_name, std::string project_folder)
{
    bool equal_name = false;

    //lista cartelle a tutti i livelli
    std::vector<std::string> dirs = get_files(project_folder);

    for(size_t i=0; i< dirs.size(); i++)
    {
        //std::cout << "Dir: " << dirs.at(i) << std::endl;
        std::string existed_name = dirs.at(i).substr(dirs.at(i).find_last_of(path_sep)+1, dirs.at(i).length());
        //std::string basename = existed_name.substr(0, existed_name.find_last_of("."));

        if(new_name.compare(existed_name) == 0)
        {
            equal_name = true;
            break;
        }
    }
    return equal_name;
}

inline
void cout_list (const std::vector<std::string> &list)
{
    for(size_t i=0; i<list.size(); i++)
    {
        std::cout << "\033[0;32m" << list.at(i) << "\033[0m" <<std::endl;
    }
}
