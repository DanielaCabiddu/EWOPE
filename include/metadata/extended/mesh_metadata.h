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

#ifndef MESH_METADATA_H
#define MESH_METADATA_H

#include "../metadata.h"

class MeshData : public EWOPE::Data
{
public:

    void set_num_verts (const unsigned int n) {num_verts = n;}
    void set_num_polys (const unsigned int n) {num_polys = n;}

    unsigned int get_num_verts () const {return num_verts;}
    unsigned int get_num_polys () const {return num_polys;}

    // Additional Methods
    bool read  (const std::string filename);
    bool write (const std::string filename);

    template <class Archive>
    void serialize( Archive & ar )
    {
        ar (CEREAL_NVP(num_verts));
        ar (CEREAL_NVP(num_polys));
    }

    template <class Archive>
    void deserialize( Archive & ar )
    {
        ar (CEREAL_NVP(num_verts));
        ar (CEREAL_NVP(num_polys));
    }

protected:

    unsigned int num_verts;
    unsigned int num_polys;
};

class MeshMetadata : public EWOPE::Metadata
{
public:

    void set_num_verts (const unsigned int n) {data.set_num_verts(n);}
    void set_num_polys (const unsigned int n) {data.set_num_polys(n);}

    unsigned int get_num_verts () const {return data.get_num_verts();}
    unsigned int get_num_polys () const {return data.get_num_polys();}

    // Additional Methods
    bool read  (const std::string filename);
    bool write (const std::string filename);

    template <class Archive>
    void serialize( Archive & ar )
    {
        ar (CEREAL_NVP(commands));
        ar (CEREAL_NVP(dependencies));
        ar (CEREAL_NVP(data));
    }

    template <class Archive>
    void deserialize( Archive & ar )
    {
        ar (CEREAL_NVP(commands));
        ar (CEREAL_NVP(dependencies));
        // ar (CEREAL_NVP(data));
    }


protected:

    MeshData data;

    bool readConfFileJSON   (const std::string filename);
    bool writeConfFileJSON  (const std::string filename);

};


#ifndef STATIC_LIB
#include "mesh_metadata.cpp"
#endif

#endif // MESH_METADATA_H
