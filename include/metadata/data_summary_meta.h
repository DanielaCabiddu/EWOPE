#ifndef DATA_SUMMARY_META_H
#define DATA_SUMMARY_META_H

#include <string>
#include <vector>

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

#include "muselib/data_structures/data.h"
#include "muselib/metadata/data_summary.h"
#include "muselib/metadata/data_statistics.h"

namespace EWOPE
{
    class DataSummaryMeta;
}

class EWOPE::DataSummaryMeta
{
public:


    // Get Methods
    const EWOPE::Data          &getData        () const    { return  data; }
    const EWOPE::DataSummary   &getSummary     () const    { return  summary; }
    const EWOPE::Statistics    &getStatistics  () const    { return  statistics; }


    // Set Methods
    void setData        (const EWOPE::Data &d)               { data = d; }
    void setSummary     (const EWOPE::DataSummary &d)        { summary = d; }
    void setStatistics  (const EWOPE::Statistics &d)         { statistics = d; }


    // Additional Methods
    bool read  (const std::string filename);
    bool write (const std::string filename);




#ifdef EWOPE_USES_CEREAL
    template <class Archive>
    void serialize( Archive & ar )
    {
        ar (CEREAL_NVP(data));
        ar (CEREAL_NVP(summary));
        ar (CEREAL_NVP(statistics));
    }

    template <class Archive>
    void deserialize( Archive & ar )
    {
        ar (CEREAL_NVP(data));
        ar (CEREAL_NVP(summary));
        ar (CEREAL_NVP(statistics));
    }
#endif

private:

    EWOPE::Data data;
    EWOPE::DataSummary summary;
    EWOPE::Statistics statistics;



    bool readConfFileJSON   (const std::string filename);
    bool writeConfFileJSON  (const std::string filename, const int &precision = 3) ;
};



#ifndef STATIC_EWOPE
#include "data_summary_meta.cpp"
#endif

#endif // DATA_SUMMARY_META_H
