#include "Point3D.h"

Point3D::Point3D() : x(0.d), y(0.d), z(0.d) {}

Point3D::Point3D(double x_coor, double y_coor, double z_coor)
{
	x = x_coor;
	y = y_coor;
	z = z_coor;
}

Point3D::Point3D(const Point3D &p)
{
	x = p.x;
	y = p.y;
	z = p.z;
}

//////////Setter//////////
void Point3D::setPoint(double x_coor, double y_coor, double z_coor){

	x = x_coor;
	y = y_coor;
	z = z_coor;
}
/////////Getters/////////
double const& Point3D::getXCoor() const
{
	return this->x;
}

double const& Point3D::getYCoor() const
{
	return this->y;
}

double const& Point3D::getZCoor() const
{
	return this->z;
}
/////////////////////////

//////Operateur <<///////
std::ostream& operator<< (std::ostream &os, const Point3D &p)
{
	return os << "x=" << p.x << ", y=" << p.y << ", z=" << p.z ;
}
