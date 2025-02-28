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
