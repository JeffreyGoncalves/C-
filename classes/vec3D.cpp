#include "vec3D.h"

vec3D::vec3D() : x_vec(0), y_vec(0), z_vec(0) {}

vec3D::vec3D(double x, double y, double z) : x_vec(x), y_vec(y), z_vec(z) {}

vec3D::vec3D(Point3D A, Point3D B)
{
	double x_A = A.getXCoor(), y_A = A.getYCoor(), z_A = A.getZCoor(),
		   x_B = B.getXCoor(), y_B = B.getYCoor(), z_B = B.getZCoor();
	
	this->x_vec = x_B - x_A;
	this->y_vec = y_B - y_A;
	this->z_vec = z_B - z_A;
}
 
//////////Getters///////////
double const& vec3D::getXCoor() const
{
	return this->x_vec;
}

double const& vec3D::getYCoor() const
{
	return this->y_vec;
}

double const& vec3D::getZCoor() const
{
	return this->z_vec;
}
		
double vec3D::getNorm()
{
	double squaredNorm = pow(x_vec, 2) + pow(y_vec, 2) + pow(z_vec, 2);
	return sqrt(squaredNorm);
}
////////////////////////////

////////Operations//////////	
double vec3D::dot(const vec3D &v)
{
	return this->x_vec * v.x_vec +
	       this->y_vec * v.y_vec +
	       this->z_vec * v.z_vec;
}

vec3D vec3D::cross(const vec3D &v) 
{
	double newX = this->y_vec * v.z_vec - this->z_vec * v.y_vec,
		   newY = this->z_vec * v.x_vec - this->x_vec * v.z_vec, 
		   newZ = this->x_vec * v.y_vec - this->y_vec * v.x_vec;
		  
	return vec3D(newX, newY, newZ);
}	

vec3D vec3D::times(const double &d)	
{
	double newX = this->x_vec * d,
		   newY = this->y_vec * d,
		   newZ = this->z_vec * d;
		   
	return vec3D(newX, newY, newZ);
}

vec3D vec3D::normalize()
{
	return this->times(1.d/this->getNorm());
}
////////////////////////////

///////Surcharge de <<//////
std::ostream& operator<< (std::ostream &os, const vec3D &v)
{
	return os << "x=" << v.x_vec << ", y=" << v.y_vec << ", z=" << v.z_vec ;
}

/*std::istream& operator>> (std::istream &is, const vec3D &v)
{
	return is >> v.x_vec >> v.y_vec >> v.z_vec;
}*/
		
