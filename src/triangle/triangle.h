#ifndef TRAINGLE_H
#define TRIANGLE_H

#include "Point3D.h"
#include "Object3D.h"
#include "color.h"
#include "ray3D.h"
#include "vec3D.h"
#include <math.h>

class Triangle : public Object3D
{
	public :
		//Constructeurs
		Triangle(Point3D A, Point3D B, Point3D C, Color color, float ref, float a);
		///////////////
		//Getters
		inline Point3D const& getP1() {return this->P1;}
		inline Point3D const& getP2() {return this->P2;}
		inline Point3D const& getPExt() {return this->PExt;}
		///////////////
		Point3D* detectCollision(ray3D ray);				//Detecte si le rayon ray rentre en contact avec la surface de l'Object3D
		vec3D calcNormToPoint(Point3D p);					//Calcule la normale au point a la surface de l'Object3D
		
	private :
		//Points du triangle
		Point3D P1;
		Point3D P2;
		Point3D PExt;
		/////////////////////
		vec3D normalVector;
		Point3D P1P2Middle;	//Sert a determiner si un point dans le plan est a distance correcte du triangle
		Point3D planOrigin;	//Sert au calcul de collision
		double alphaP1;		//Idem
		double alphaP2;		//Idem
		double a, b, c, d;	//Coefficients necessaire pour la detection de collision
		
		const static double PI  =3.141592653589793238463;
};

#endif
