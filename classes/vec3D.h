#ifndef VEC3D_H
#define VEC3D_H

#include <iostream>
#include <math.h>
#include "Point3D.h"

class vec3D
{
	public :
		//Constructeurs
		vec3D();
		vec3D(double x, double y, double z);
		vec3D(Point3D A, Point3D B);				//Calcul d'un vecteur grace a deux points
		///////////////
		//Getters
		double const& getXCoor() const;
		double const& getYCoor() const;
		double const& getZCoor() const;
		double getNorm();				//Donne la norme du vecteur
		///////////////
		//Operations (on n'effectue pas de surcharge d'operateur car ambigue entre produit scalaire et vectoriel)
		double dot(const vec3D &v);		//Represente le produit scalaire
		vec3D cross(const vec3D &v); 	//Represente le produit vectoriel
		vec3D times(const double &d);	//Represente le produit entre un vec3D et un scalaire
		vec3D normalize();				//Normalise le vecteur et renvoie celle ci en copie
		///////////////
		//Surcharge des operateurs <<
		friend std::ostream& operator<< (std::ostream &os, const vec3D &v);
		//friend std::istream& operator>> (std::istream &is, vec3D &v);
		
		
	private :
		double x_vec, y_vec, z_vec;
};

#endif
