#ifndef DATA_SUMMARY_H
#define DATA_SUMMARY_H

#include <string>
#include <vector>

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

#include "data_structures/data.h"

namespace MUSE
{
    class DataSummary;
}

class MUSE::DataSummary
{
public:

    unsigned int n_samples = 0;
    unsigned int n_positive_values = 0;
    unsigned int n_negative_values = 0;
    unsigned int n_nd_values = 0; //not detected
    unsigned int n_allowed_symbols = 0;
    unsigned int n_empty = 0;
    unsigned int n_valid_values = 0;


    // Add any other additional descriptive info
    #ifdef MUSE_USES_CEREAL
        template <class Archive>
        void serialize( Archive & ar )
        {
            ar (CEREAL_NVP(n_samples));
            ar (CEREAL_NVP(n_positive_values));
            ar (CEREAL_NVP(n_negative_values));
            ar (CEREAL_NVP(n_nd_values));
            ar (CEREAL_NVP(n_allowed_symbols));
            ar (CEREAL_NVP(n_empty));
            ar (CEREAL_NVP(n_valid_values));
        }

        template <class Archive>
        void deserialize( Archive & ar )
        {
            ar (CEREAL_NVP(n_samples));
            ar (CEREAL_NVP(n_positive_values));
            ar (CEREAL_NVP(n_negative_values));
            ar (CEREAL_NVP(n_nd_values));
            ar (CEREAL_NVP(n_allowed_symbols));
            ar (CEREAL_NVP(n_empty));
            ar (CEREAL_NVP(n_valid_values));
        }
    #endif


    // Get Methods
    //const DataSummary   &getSummary             () const    { return  summary; }

    // Set Methods
    void setSummary     (const MUSE::Data &data);


    // Additional Methods
    bool read  (const std::string filename);
    bool write (const std::string filename);





private:

    //DataSummary summary;

    bool readConfFileJSON   (const std::string filename);
    bool writeConfFileJSON  (const std::string filename) ;
};



#ifndef STATIC_MUSELIB
#include "data_summary.cpp"
#endif

#endif // DATA_SUMMARY_H
