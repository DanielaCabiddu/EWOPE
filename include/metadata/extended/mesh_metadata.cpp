#include "mesh_metadata.h"

#include <iostream>
#include <fstream>

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


bool MeshMetadata::read(const std::string filename)
{
    return readConfFileJSON(filename);
}

bool MeshMetadata::write(const std::string filename)
{
    return writeConfFileJSON(filename);
}

bool MeshMetadata::readConfFileJSON(const std::string filename)
{
    std::ifstream ss (filename.c_str(), std::ifstream::in);

    if (!ss.is_open())
    {
        std::cerr << "[ERROR] Error in opening " << filename << "." << std::endl;
        std::cerr << "[ERROR] Configuration file cannot be read from disk." << std::endl;
        return false;
    }

    cereal::JSONInputArchive archive (ss);
    deserialize(archive);
    ss.close();

    return true;
}

// //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


bool MeshMetadata::writeConfFileJSON (const std::string filename)
{
    std::ofstream ss (filename.c_str(), std::ofstream::out);

    if (!ss.is_open())
    {
        std::cerr << "[ERROR] Error in opening " << filename << "." << std::endl;
        std::cerr << "[ERROR] Configuration file cannot be written on disk." << std::endl;
        return false;
    }

    {
        cereal::JSONOutputArchive archive (ss);
        serialize(archive);
    }
    ss.close();

    return true;
}
