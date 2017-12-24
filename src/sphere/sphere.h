#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <cstdio>
#include "Point3D.h"
#include "color.h"
#include "Object3D.h"
#include "vec3D.h"
#include "ray3D.h"

class Sphere : public Object3D
{
	public:
		//Constructeurs
		Sphere();
		Sphere(double x,double y, double z, double r, Color C, float ref, float a);
		~Sphere(){}
		///////////////
		//Setters
		void setCenter(double x, double y , double z);
		void setCenter(Point3D new_center);
		///////////////
		Point3D* detectCollision(ray3D ray);			//Detecte si le rayon ray rentre en contact avec la surface de la sphere
		vec3D calcNormToPoint(Point3D p);				//Calcule la normale au point a la surface de la sphere
		//Operateur << 
		friend std::ostream& operator<< (std::ostream &os, const Sphere &s);
		///////////////
	
	private :
		Point3D center;						// coordonnées du centre de la sphère
		double radius;					 	// rayon  				  
};

#endif
