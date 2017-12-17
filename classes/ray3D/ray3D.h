#ifndef RAY3D_H
#define RAY3D_H

#include <iostream>

#include "Point3D.h"
#include "vec3D.h"

class ray3D
{
	public :
		ray3D();
		ray3D(Point3D origin_p, vec3D rayDirection_p);
		ray3D(double x_origin, double y_origin, double z_origin, double x_rayDir, double y_rayDir, double z_rayDir);
		//getters
		Point3D const& getOrigin() const;
		vec3D const& getRayDirection() const;
		// << redefinition
		friend std::ostream& operator<< (std::ostream &os, const ray3D &ray);
	
	private :
		Point3D origin;
		vec3D rayDirection;
};

#endif
