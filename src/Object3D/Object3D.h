#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <iostream>
#include <math.h>
#include <cstdio>
#include "Point3D.h"
#include "ray3D.h"
#include "vec3D.h"
#include "color.h"

class Object3D
{
	public :
		//Constructeurs
		Object3D();
		Object3D(Color C, float ref, float a);
		virtual ~Object3D();
		///////////////
		//Getters
		Color const& getObjectColor();
		float const& getObjectReflexionFactor();
		float const& getObjectAlpha();
		///////////////
		virtual Point3D* detectCollision(ray3D ray) = 0;				//Detecte si le rayon ray rentre en contact avec la surface de l'Object3D
		virtual vec3D calcNormToPoint(Point3D p) = 0;					//Calcule la normale au point a la surface de l'Object3D
		ray3D calcReflexionRay(Point3D reflectedRayOrigin, ray3D r);	//Calcule le rayon reflechi par la surface de l'Object3D
		
	private :
		Color rgb;					// niveaux RGB
		float reflexion;			// indice de réflexion
		float alpha;				// indice de transparence
};

#endif
