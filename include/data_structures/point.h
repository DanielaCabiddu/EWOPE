#ifndef POINT_H
#define POINT_H

#include <string>
#include <vector>
#include <iostream>

namespace EWOPE
{
    class Point2D;
    class Point3D;
}

class EWOPE::Point2D
{
    public:

        std::string id;
        double x;
        double y;
};

class EWOPE::Point3D
{
    public:

        std::string id;
        double x;
        double y;
        double z;
        int index;
        //Point3D(double a, double b, double c): x(a), y(b), z(c) {}
};


double  dist         (EWOPE::Point2D p0, EWOPE::Point2D p1);
double  sqrt_dist    (EWOPE::Point2D p0, EWOPE::Point2D p1);

double  dist3D       (EWOPE::Point3D p0, EWOPE::Point3D p1);
bool    comparePoint (EWOPE::Point3D p0, EWOPE::Point3D p1);

bool    equalPoint   (EWOPE::Point3D p0, EWOPE::Point3D p1);

EWOPE::Point3D rotPoint (EWOPE::Point3D p0, const std::string &rot_axis, const double &rot_angle);

std::vector<EWOPE::Point3D> remove_duplicates (std::vector<EWOPE::Point3D> &points, double threshold = 1e-6);
void remove_duplicates (std::vector<EWOPE::Point3D> &points, std::vector<EWOPE::Point3D> &unique_points, std::vector<int> &unique_points_id, double threshold = 1e-6);
void remove_duplicates (const std::vector<double> &points_x, const std::vector<double> &points_y, std::vector<int> &unique_points_id, std::vector<double> &unique_points_x, std::vector<double> &unique_points_y, double threshold = 1e-6);


EWOPE::Point2D linear_interpolation (EWOPE::Point2D p0, EWOPE::Point2D p1, const double &t);
EWOPE::Point2D pixel2world ( const int& x, const int& y, const double &raster_width, const double &raster_height);


#ifndef STATIC_EWOPE
#include "point.cpp"
#endif


#endif // POINT_H
