#ifndef ECRAN_H
#define ECRAN_H

#include <iostream>
#include "Point3D.h"
#include "vec3D.h"
class Ecran
{
	public:
		//CONSTRUCTEUR
		Ecran(Point3D topL,Point3D topR, Point3D botL, int horizontalRes);
	
		//GETTER 
		Point3D const& getLeftBottom();
		Point3D const& getLeftTop();
		Point3D const& getRightTop();
		Point3D const& getRightBottom();
		int const& getHorizontalResolution();
		int const& getVerticalResolution();

	private:
		Point3D leftBottom,leftTop;
		Point3D rightBottom,rightTop;
		int HResolution, VResolution;
		//Methode privee pour calculer le quatrieme point de l'ecran
		Point3D FindRightBottom(Point3D topL,Point3D topR,Point3D botL);
		//Methode privee qui retourne la hauteur de l'ecran en pixels
		double calcVerticalResolution();

};

#endif
