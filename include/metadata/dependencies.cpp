#include "dependencies.h"

#include "muselib/metadata/data_meta.h"
#include "muselib/metadata/metadata.h"
#include "muselib/metadata/extraction_meta.h"
#include "muselib/metadata/manipulate_meta.h"
#include "muselib/metadata/surface_meta.h"
#include "muselib/metadata/volume_meta.h"
#include "muselib/metadata/vario_meta.h"
#include "muselib/metadata/compute_meta.h"


bool findDeps_from_JSON (const std::string &JSONfilename)
{
    bool find_deps = false;
    std::vector<std::string> apps {"data", "geometry", "manipulate", "vario", "compute"};

    std::string loc;
    for(const std::string &name:apps)
    {
        if(JSONfilename.find(name) != std::string::npos)
        {
            loc = name;
            break;
        }
    }

    if(loc == apps[0])
    {
        //MUSE DATA META
        MUSE::Metadata datameta;
        datameta.read(JSONfilename);

        if(datameta.getDeps().size() > 0)
            find_deps = true;
    }
    else if(loc == apps[1] && JSONfilename.find("surf") != std::string::npos)
    {
        //MUSE GEOMETRY META
        MUSE::SurfaceMeta surfmeta;
        surfmeta.read(JSONfilename);

        if(surfmeta.getDeps().size() > 0)
            find_deps = true;
    }
    else if(loc == apps[1] && JSONfilename.find("volume") != std::string::npos)
    {
        //MUSE GEOMETRY META
        MUSE::VolumeMeta volmeta;
        volmeta.read(JSONfilename);

        if(volmeta.getDeps().size() > 0)
            find_deps = true;
    }
    else if(loc == apps[2])
    {
        //MUSE MANIPULATE META
        MUSE::ExtractionMeta extrmeta;
        extrmeta.read(JSONfilename);

        if(extrmeta.getDeps().size() > 0)
            find_deps = true;
    }
    else if(loc == apps[3])
    {
        //MUSE VARIO META
        MUSE::VarioMeta variometa;
        variometa.read(JSONfilename);

        if(variometa.getDeps().size() > 0)
            find_deps = true;
    }
    else if(loc == apps[4] && JSONfilename.find("_sgs") == std::string::npos)
    {
        //MUSE COMPUTE META
        MUSE::ComputeMeta computemeta;
        computemeta.read(JSONfilename);

        if(computemeta.getDeps().size() > 0)
            find_deps = true;
    }
    else if(loc == apps[4])
    {
        //MUSE DATA META
        MUSE::Metadata datameta;
        datameta.read(JSONfilename);

        if(datameta.getDeps().size() > 0)
            find_deps = true;
    }
    return find_deps;
}


std::vector<std::string> getDeps_from_JSON(const std::string &JSONfilename)
{
    std::vector<std::string> deps;
    std::vector<std::string> apps {"data", "geometry", "manipulate", "vario", "compute"};

    std::string loc;
    for(const std::string &name:apps)
    {
        if(JSONfilename.find(name) != std::string::npos)
        {
            loc = name;
            break;
        }
    }

    std::string key0 = "samples_";
    std::string key1 = "geom_";

    if(loc == apps[0])
    {
        //MUSE DATA META
        MUSE::Metadata datameta;
        datameta.read(JSONfilename);

        deps = datameta.getDeps();
    }
    else if(loc == apps[1] && JSONfilename.find("surf") != std::string::npos)
    {
        //MUSE GEOMETRY META
        MUSE::SurfaceMeta surfmeta;
        surfmeta.read(JSONfilename);

        deps = surfmeta.getDeps();
    }
    else if(loc == apps[1] && JSONfilename.find("volume") != std::string::npos)
    {
        //MUSE GEOMETRY META
        MUSE::VolumeMeta volmeta;
        volmeta.read(JSONfilename);

        deps = volmeta.getDeps();
    }
    else if(loc == apps[2] && JSONfilename.find(key0) != std::string::npos)
    {
        //MUSE MANIPULATE META
        MUSE::ManipulateMeta extrmeta;
        extrmeta.read(JSONfilename);

        deps = extrmeta.getDeps();
    }
    else if(loc == apps[2] && JSONfilename.find(key1) != std::string::npos)
    {
        //MUSE MANIPULATE META
        MUSE::ManipulateMeta extrmeta;
        extrmeta.read(JSONfilename);

        deps = extrmeta.getDeps();
    }
    else if(loc == apps[2])
    {
        //MUSE MANIPULATE META
        MUSE::ExtractionMeta extrmeta;
        extrmeta.read(JSONfilename);

        deps = extrmeta.getDeps();
    }
    else if(loc == apps[3])
    {
        //MUSE VARIO META
        MUSE::VarioMeta variometa;
        variometa.read(JSONfilename);

        deps = variometa.getDeps();
    }
    else if(loc == apps[4] && JSONfilename.find("_sgs") == std::string::npos)
    {
        //MUSE COMPUTE META
        MUSE::ComputeMeta computemeta;
        computemeta.read(JSONfilename);

        deps = computemeta.getDeps();
    }
    else if(loc == apps[4])
    {
        //MUSE DATA META
        MUSE::Metadata datameta;
        datameta.read(JSONfilename);

        deps = datameta.getDeps();
    }
    return deps;
}

std::vector<std::string> getCom_from_JSON(const std::string &JSONfilename)
{
    std::vector<std::string> deps;
    std::vector<std::string> apps {"data", "geometry", "manipulate", "vario", "compute"};

    std::string loc;
    for(const std::string &name:apps)
    {
        if(JSONfilename.find(name) != std::string::npos)
        {
            loc = name;
            break;
        }
    }

    std::string key0 = "samples_";
    std::string key1 = "geom_";

    if(loc == apps[0])
    {
        //MUSE DATA META
        MUSE::Metadata datameta;
        datameta.read(JSONfilename);

        deps = datameta.getCommands();
    }
    else if(loc == apps[1] && JSONfilename.find("surf") != std::string::npos)
    {
        //MUSE GEOMETRY META
        MUSE::SurfaceMeta surfmeta;
        surfmeta.read(JSONfilename);

        deps = surfmeta.getCommands();
    }
    else if(loc == apps[1] && JSONfilename.find("volume") != std::string::npos)
    {
        //MUSE GEOMETRY META
        MUSE::VolumeMeta volmeta;
        volmeta.read(JSONfilename);

        deps = volmeta.getCommands();
    }
    else if(loc == apps[2] && JSONfilename.find(key0) != std::string::npos)
    {
        //MUSE MANIPULATE META
        MUSE::ManipulateMeta extrmeta;
        extrmeta.read(JSONfilename);

        deps = extrmeta.getCommands();
    }
    else if(loc == apps[2] && JSONfilename.find(key1) != std::string::npos)
    {
        //MUSE MANIPULATE META
        MUSE::ManipulateMeta extrmeta;
        extrmeta.read(JSONfilename);

        deps = extrmeta.getCommands();
    }
    else if(loc == apps[2])
    {
        //MUSE MANIPULATE META
        MUSE::ExtractionMeta extrmeta;
        extrmeta.read(JSONfilename);

        deps = extrmeta.getCommands();
    }
    else if(loc == apps[3])
    {
        //MUSE VARIO META
        MUSE::VarioMeta variometa;
        variometa.read(JSONfilename);

        deps = variometa.getCommands();
    }
    else if(loc == apps[4] && JSONfilename.find("_sgs") == std::string::npos)
    {
        //MUSE COMPUTE META
        MUSE::ComputeMeta computemeta;
        computemeta.read(JSONfilename);

        deps = computemeta.getCommands();
    }
    else if(loc == apps[4])
    {
        //MUSE DATA META
        MUSE::Metadata datameta;
        datameta.read(JSONfilename);

        deps = datameta.getCommands();
    }
    return deps;
}

void getDeps_from_JSON_extended(const std::string &JSONfilename, std::vector<std::string> &deps, std::vector<std::string> &commands)
{
    std::vector<std::string> apps {"data", "geometry", "manipulate", "vario", "compute"};

    std::string loc;
    for(const std::string &name:apps)
    {
        if(JSONfilename.find(name) != std::string::npos)
        {
            loc = name;
            break;
        }
    }

    std::string key0 = "samples_";
    std::string key1 = "geom_";

    if(loc == apps[0])
    {
        //MUSE DATA META
        MUSE::Metadata datameta;
        datameta.read(JSONfilename);

        deps = datameta.getDeps();
        commands = datameta.getCommands();
    }
    else if(loc == apps[1] && JSONfilename.find("surf") != std::string::npos)
    {
        //MUSE GEOMETRY META
        MUSE::SurfaceMeta surfmeta;
        surfmeta.read(JSONfilename);

        deps = surfmeta.getDeps();
        commands = surfmeta.getCommands();
    }
    else if(loc == apps[1] && JSONfilename.find("volume") != std::string::npos)
    {
        //MUSE GEOMETRY META
        MUSE::VolumeMeta volmeta;
        volmeta.read(JSONfilename);

        deps = volmeta.getDeps();
        commands = volmeta.getCommands();
    }
    else if(loc == apps[2] && JSONfilename.find(key0) != std::string::npos)
    {
        //MUSE MANIPULATE META
        MUSE::ManipulateMeta extrmeta;
        extrmeta.read(JSONfilename);

        deps = extrmeta.getDeps();
        commands = extrmeta.getCommands();
    }
    else if(loc == apps[2] && JSONfilename.find(key1) != std::string::npos)
    {
        //MUSE MANIPULATE META
        MUSE::ManipulateMeta extrmeta;
        extrmeta.read(JSONfilename);

        deps = extrmeta.getDeps();
        commands = extrmeta.getCommands();
    }
    else if(loc == apps[2])
    {
        //MUSE MANIPULATE META
        MUSE::ExtractionMeta extrmeta;
        extrmeta.read(JSONfilename);

        deps = extrmeta.getDeps();
        commands = extrmeta.getCommands();
    }
    else if(loc == apps[3])
    {
        //MUSE VARIO META
        MUSE::VarioMeta variometa;
        variometa.read(JSONfilename);

        deps = variometa.getDeps();
        commands = variometa.getCommands();
    }
    else if(loc == apps[4] && JSONfilename.find("_sgs") == std::string::npos)
    {
        //MUSE COMPUTE META
        MUSE::ComputeMeta computemeta;
        computemeta.read(JSONfilename);

        deps = computemeta.getDeps();
        commands = computemeta.getCommands();
    }
    else if(loc == apps[4])
    {
        //MUSE DATA META
        MUSE::Metadata datameta;
        datameta.read(JSONfilename);

        deps = datameta.getDeps();
        commands = datameta.getCommands();
    }
}
