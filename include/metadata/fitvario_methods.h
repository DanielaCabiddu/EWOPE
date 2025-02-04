#ifndef FITVARIO_METHODS_H
#define FITVARIO_METHODS_H

#include <string>
#include <vector>

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

// #include <geostatslib/statistics/data_structures.h>
// #include <geostatslib/statistics/variogram.h>

namespace EWOPE
{

class variogram_methods /*: public variogram*/
{
    public:

    // Set Methods
    void setDirection       (const double d)                {degree_direction = d; }
    void setNugget          (const double n)                {nugget = n; }
    void setSill            (const double s)                {sill = s; }
    void setType            (const std::string t)           {type = t; }


    // Get Methods
    double              getDirection        ()  const       {return degree_direction;}
    double              getNugget           ()  const       {return nugget; }
    double              getSill             ()  const       {return sill; }
    std::string         getType             ()  const       {return type; }



#ifdef EWOPE_USES_CEREAL
    template <class Archive>
    void serialize( Archive & ar )
    {
        ar (CEREAL_NVP (degree_direction));
        ar (CEREAL_NVP (type));
        ar (CEREAL_NVP (nugget));
        ar (CEREAL_NVP (sill));
        ar (CEREAL_NVP (range));
        ar (CEREAL_NVP (range_max));
        ar (CEREAL_NVP (range_min));
    }

    template <class Archive>
    void deserialize( Archive & ar )
    {
        ar (CEREAL_NVP (degree_direction));
        ar (CEREAL_NVP (type));
        ar (CEREAL_NVP (nugget));
        ar (CEREAL_NVP (sill));
        ar (CEREAL_NVP (range));
        ar (CEREAL_NVP (range_max));
        ar (CEREAL_NVP (range_min));
    }
#endif

private:

    double degree_direction = 0.0;

    double nugget;
    double sill;
    double range;

    std::string type;

    double range_min;
    double range_max;
};

}


#endif // FITVARIO_METHODS_H
