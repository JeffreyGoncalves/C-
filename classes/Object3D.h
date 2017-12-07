#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <iostream>
#include <cstdio>
#include "Point3D.h"
#include "color.h"

class Object3D
{
	public :
		Object3D();
		Object3D(Color C, float ref);
		virtual Point3D* detectCollision(Point3D rayOrigin, Point3D rayDirection) = 0;
		
	private :
		Color rgb;					// niveaux RGB
		float reflexion;			// indice de réflexion
};

#endif
