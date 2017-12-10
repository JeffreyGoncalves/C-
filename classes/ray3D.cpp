#include "ray3D.h"

ray3D::ray3D() : origin(), rayDirection() {}

ray3D::ray3D(Point3D origin_t, vec3D rayDirection_t)
{
	this->origin = origin_t;
	this->rayDirection = rayDirection_t;
}

ray3D::ray3D(double x_origin, double y_origin, double z_origin, double x_rayDir, double y_rayDir, double z_rayDir) :
	origin(x_origin, y_origin, z_origin), 
	rayDirection(x_rayDir, y_rayDir, z_rayDir) {}
	

///////Getters////////
Point3D const& ray3D::getOrigin() const
{
	return this->origin;
}

vec3D const& ray3D::getRayDirection() const
{
	return this->rayDirection;
}
//////////////////////
