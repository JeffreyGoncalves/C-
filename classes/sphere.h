#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <cstdio>
#include "Point3D.h"
#include "color.h"
#include "Object3D.h"

class Sphere : public Object3D
{
	public:
		Sphere();
		Sphere(float x,float y, float z, float r, Color C, float ref);
		
		void setCenter(float x, float y , float z);
		void setCenter(Point3D new_center);
		Point3D* detectCollision(Point3D rayOrigin, Point3D rayDirection);
	
	private :
		Point3D center;						// coordonnées du centre de la sphère
		float radius;					 	// rayon  				  
};

#endif
