#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <string>

#include <json.hpp>
using json = nlohmann::ordered_json;

#include <cereal/archives/json.hpp>

enum geomType
{
    POLYGON, //0
    POINT,  //1
    MULTI,    //2
    LINESTRING
};

namespace EWOPE
{
    class GeospatialData;
}

class EWOPE::GeospatialData
{
    public:

        std::string name;
        std::string format;
        std::string authority = "Unknown";

        geomType    geom_type;

        std::string units = ""; //da settare

        int         n_subdomains = 0; //numbers of sub-domains
        std::string id_subdomain;     //id sub-domain


        // Get Methods
        const std::string getName        ()  const { return name; }
        const std::string getFormat      ()  const { return format; }
        const std::string getAuthority   ()  const { return authority; }
              int getDomains             ()  const { return n_subdomains; }


        // Set Methods
        void setName        (const std::string s)  { name = s; }
        void setFormat      (const std::string s)  { format = s; }
        void setAuthority   (const std::string s)  { authority = s; }
        void setDomains     (      int n)          { n_subdomains = n; }


    #ifdef EWOPE_USES_CEREAL
        template <class Archive>
        void serialize( Archive & ar )
        {
            ar (CEREAL_NVP(name));
            ar (CEREAL_NVP(format));
            ar (CEREAL_NVP(authority));
            ar (CEREAL_NVP(units));
            ar (CEREAL_NVP(n_subdomains));
            ar (CEREAL_NVP(id_subdomain));
        }

        template <class Archive>
        void deserialize( Archive & ar )
        {
            ar (CEREAL_NVP(name));
            ar (CEREAL_NVP(format));
            ar (CEREAL_NVP(authority));
            ar (CEREAL_NVP(units));
            ar (CEREAL_NVP(n_subdomains));
            ar (CEREAL_NVP(id_subdomain));
        }
    #endif

};

void setGeometryType        (EWOPE::GeospatialData &geometry, std::string &GDALtype);
void updateProjectJson      (const EWOPE::GeospatialData &geometry, json &metadata);
void updateJson             (const EWOPE::GeospatialData &geometry, json &metadata);


#ifndef STATIC_MUSELIB
#include "geometry.cpp"
#endif

#endif // GEOMETRY_H
