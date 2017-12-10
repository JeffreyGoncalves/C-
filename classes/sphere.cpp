#include "sphere.h"
 
Sphere::Sphere(double x, double y, double z, double r, Color C, double ref) : Object3D(C, ref), center(x,y,z), radius(r) {}

Sphere::Sphere() : Object3D(), center(), radius(0.d) {}

void Sphere::setCenter(double x, double y, double z){

	Point3D new_center(x,y,z);
	center = new_center;
}

void Sphere::setCenter(Point3D new_center)
{
	center = new_center;
}

Point3D* Sphere::detectCollision(ray3D ray)
{
	return NULL;
}

vec3D Sphere::calcNormToPoint(Point3D p)
{
	vec3D v(this->center, p);
	return v.normalize();
}

//Surcharge de << 
std::ostream& operator<< (std::ostream &os, const Sphere &s)
{
	return os << "center=" << s.center << ", radius=" << s.radius;
}
