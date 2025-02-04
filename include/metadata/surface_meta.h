#ifndef SURFACE_META_H
#define SURFACE_META_H

#include <string>

#include "muselib/data_structures/point.h"
#include "muselib/data_structures/project.h"
#include "muselib/data_structures/geometry.h"
#include "muselib/data_structures/surface.h"
#include "muselib/data_structures/volume.h"
#include "muselib/data_structures/rotation.h"

namespace EWOPE
{
    class SurfaceMeta;
}

class EWOPE::SurfaceMeta
{
public:

    struct DataSummary
    {
        double  x_min = DBL_MAX;
        double  x_max = -DBL_MAX;
        double  y_min = DBL_MAX;
        double  y_max = -DBL_MAX;
        double  z_min = DBL_MAX;
        double  z_max = -DBL_MAX;


        // Add any other additional descriptive info

        #ifdef EWOPE_USES_CEREAL
        template <class Archive>
        void serialize( Archive & ar )
        {
            ar (CEREAL_NVP(x_min));
            ar (CEREAL_NVP(x_max));
            ar (CEREAL_NVP(y_min));
            ar (CEREAL_NVP(y_max));
            ar (CEREAL_NVP(z_min));
            ar (CEREAL_NVP(z_max));
        }

        template <class Archive>
        void deserialize( Archive & ar )
        {
            ar (CEREAL_NVP(x_min));
            ar (CEREAL_NVP(x_max));
            ar (CEREAL_NVP(y_min));
            ar (CEREAL_NVP(y_max));
            ar (CEREAL_NVP(z_min));
            ar (CEREAL_NVP(z_max));
        }
        #endif

        void setDataSummary     (const std::vector<Point3D> &d);

    };

    struct Extrusion
    {
        std::string type;
        std::string direction;
        double      value = 0.0;

        // Add any other additional descriptive info

        #ifdef EWOPE_USES_CEREAL
        template <class Archive>
        void serialize( Archive & ar )
        {
            ar (CEREAL_NVP(type));
            ar (CEREAL_NVP(direction));
            ar (CEREAL_NVP(value));
        }

        template <class Archive>
        void deserialize( Archive & ar )
        {
            ar (CEREAL_NVP(type));
            ar (CEREAL_NVP(direction));
            ar (CEREAL_NVP(value));
        }
        #endif
    };


    // Get Methods
    const EWOPE::Project         &getProject         () const    { return  project; }

    const std::vector<std::string> &getCommands () const    { return commands;}
    const std::string &getCommand (const unsigned int i) const { return commands.at(i); }

    const std::vector<std::string> &getDeps () const { return  dependencies; }
    const std::string &getDep (const unsigned int i) const { return  dependencies.at(i); }

    const EWOPE::GeospatialData  &getGeospatialData  () const    { return geospatialdata; }
    const DataSummary           &getDataSummary     () const    { return data_summary; }

    const EWOPE::Rotation        &getDataRotation    () const    { return data_rotation; }
    const Extrusion             &getExtrusion      () const     { return extrusion; }
    const EWOPE::Surface         &getMeshSummary     () const    { return mesh; }



    // Set Methods
    void setProject         (const EWOPE::Project &d)        { project = d; }

    void setCommands        (const std::vector<std::string> &d) { commands = d; }
    void setDependencies    (const std::vector<std::string> &d) { dependencies = d; }

    void setGeospatialData  (const EWOPE::GeospatialData &d) { geospatialdata = d; }


    void setDataSummary     (const DataSummary &d)          { data_summary = d; }

    void setDataRotation    (const EWOPE::Rotation &d)       { data_rotation = d; }
    void setExtrusion       (const Extrusion &d)            { extrusion = d; }
    void setMeshSummary     (const EWOPE::Surface &d)        { mesh = d; }



    // Additional Methods
    bool read  (const std::string filename);
    bool write (const std::string filename);

#ifdef EWOPE_USES_CEREAL
    template <class Archive>
    void serialize( Archive & ar )
    {
        ar (CEREAL_NVP(project));
        ar (CEREAL_NVP(commands));
        ar (CEREAL_NVP(dependencies));
        ar (CEREAL_NVP(geospatialdata));
        ar (CEREAL_NVP(data_summary));
        ar (CEREAL_NVP(data_rotation));
        ar (CEREAL_NVP(extrusion));
        ar (CEREAL_NVP(mesh));
    }

    template <class Archive>
    void deserialize( Archive & ar )
    {
        ar (CEREAL_NVP(project));
        ar (CEREAL_NVP(commands));
        ar (CEREAL_NVP(dependencies));
        ar (CEREAL_NVP(geospatialdata));
        ar (CEREAL_NVP(data_summary));
        ar (CEREAL_NVP(data_rotation));
        ar (CEREAL_NVP(extrusion));
        ar (CEREAL_NVP(mesh));
    }
#endif

private:

    EWOPE::Project project;
    std::vector<std::string> commands;
    std::vector<std::string> dependencies;

    EWOPE::GeospatialData geospatialdata;
    DataSummary data_summary;
    EWOPE::Rotation data_rotation;
    Extrusion extrusion;
    EWOPE::Surface mesh;



    bool readConfFileJSON   (const std::string filename);
    bool writeConfFileJSON  (const std::string filename, const int &precision = 3) ;
};



#ifndef STATIC_EWOPE
#include "surface_meta.cpp"
#endif

#endif // SURFACE_META_H
