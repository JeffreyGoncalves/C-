#ifndef TPYRAMID_H
#define TPYRAMID_H

#include "Point3D.h"
#include "Object3D.h"
#include "color.h"
#include "ray3D.h"
#include "vec3D.h"
#include "triangle.h"
#include <math.h>

class TPyramid : public Object3D
{
	public :
		//Constructeurs
		TPyramid(Point3D A, Point3D B, Point3D C, Point3D topPoint, Color color, float ref, float a, float refrac);
		///////////////
		//Getters
		inline Point3D const& getP1() {return this->P1;}
		inline Point3D const& getP2() {return this->P2;}
		inline Point3D const& getP3() {return this->P3;}
		inline Point3D const& getPTop() {return this->PTop;}
		///////////////
		Point3D* detectCollision(ray3D ray);				//Detecte si le rayon ray rentre en contact avec la surface de l'Object3D
		vec3D calcNormToPoint(Point3D p);					//Calcule la normale au point a la surface de l'Object3D
		
	private :
		//Points du triangle
		Triangle listTriangle[4];		//Les 3 triangles qui composent la pyramide : 0=base, 1,2,3 = cotés
		Point3D P1;						//Point 1 de la base
		Point3D P2;						//Point 2 de la base
		Point3D P3;						//Point 3 de la base
		Point3D PTop;					//Point de la pointe de la pyramide
		/////////////////////
};

#endif
