#ifndef VARIO_METHODS_H
#define VARIO_METHODS_H

#include <string>
#include <vector>

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

// #include <geostatslib/statistics/variogram.h>


namespace EWOPE
{

class exp_variog_methods /*: public exp_variog*/
{
    public:

    // Set Methods
    void setDirection       (const double d)                {degree_direction = d; }
    void setExpVariog_gamma (const std::vector<double> g)   {gamma = g; }
    void setExpVariog_h     (const std::vector<double> g)   {h = g; }
    void setExpVariog_N     (const std::vector<unsigned int> g)     {N = g; }


    // Get Methods
    double              getDirection        ()  const       {return degree_direction;}
    std::vector<double> getExpVariog_gamma  ()  const       {return gamma;}
    std::vector<double> getExpVariog_h      ()  const       {return h;}
    std::vector<unsigned int>   getExpVariog_N      ()  const       {return N;}



#ifdef EWOPE_USES_CEREAL
    template <class Archive>
    void serialize( Archive & ar )
    {
        ar (CEREAL_NVP (degree_direction));
        ar (CEREAL_NVP (gamma));
        ar (CEREAL_NVP (h));
        ar (CEREAL_NVP (N));
    }

    template <class Archive>
    void deserialize( Archive & ar )
    {
        ar (CEREAL_NVP (degree_direction));
        ar (CEREAL_NVP (gamma));
        ar (CEREAL_NVP (h));
        ar (CEREAL_NVP (N));
    }
#endif

private:

    double degree_direction;

    std::vector<double> gamma;
    std::vector<double> h;
    std::vector<unsigned int> N;
};

}



#endif // VARIO_METHODS_H
