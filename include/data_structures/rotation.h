#ifndef ROTATION_H
#define ROTATION_H

#include <string>

#include <cereal/archives/json.hpp>

namespace EWOPE
{
    class Rotation;
}
class EWOPE::Rotation
{
    public:

    bool        rotation = false;
    std::string rotation_axis;
    double      rotation_center_x = 0.0;
    double      rotation_center_y = 0.0;
    double      rotation_center_z = 0.0;
    double      rotation_angle = 0.0;

    // Add any other additional descriptive info

    #ifdef EWOPE_USES_CEREAL
    template <class Archive>
    void serialize( Archive & ar )
    {
        ar (CEREAL_NVP(rotation));
        ar (CEREAL_NVP(rotation_axis));
        ar (CEREAL_NVP(rotation_center_x));
        ar (CEREAL_NVP(rotation_center_y));
        ar (CEREAL_NVP(rotation_center_z));
        ar (CEREAL_NVP(rotation_angle));
    }

    template <class Archive>
    void deserialize( Archive & ar )
    {
        ar (CEREAL_NVP(rotation));
        ar (CEREAL_NVP(rotation_axis));
        ar (CEREAL_NVP(rotation_center_x));
        ar (CEREAL_NVP(rotation_center_y));
        ar (CEREAL_NVP(rotation_center_z));
        ar (CEREAL_NVP(rotation_angle));
    }
    #endif

};

#endif // ROTATION_H
