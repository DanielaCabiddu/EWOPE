#include "surface.h"


template<class M, class V, class E, class P>
void EWOPE::Surface::setSummary(const cinolib::AbstractPolygonMesh<M,V,E,P> &mesh)
{
    this->summary.nverts = mesh.num_verts();
    this->summary.nedges = mesh.num_edges();
    this->summary.npolys = mesh.num_polys();

    this->summary.min_edge = mesh.edge_min_length();
    this->summary.max_edge = mesh.edge_max_length();
    this->summary.avg_edge = mesh.edge_avg_length();

    this->summary.bbox_dx = mesh.bbox().delta_x();
    this->summary.bbox_dy = mesh.bbox().delta_y();
    this->summary.bbox_dz = mesh.bbox().delta_z();

    this->summary.area = mesh.mesh_area();
}
