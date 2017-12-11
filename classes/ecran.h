#ifndef ECRAN_H
#define ECRAN_H

#include <iostream>
#include "Point3D.h"
class Ecran
{
public:
	//CONSTRUCTEUR
	Ecran(Point3D topL,Point3D topR, Point3D botL,int r);

	//methode pour calculer le quatrieme point de l'ecran
	void FindRightBottom(Point3D topL,Point3D topR,Point3D botL);

	//Methode qui retourne la hauteur de l'ecran en pixels
	double getPixelHeight();
	


	//GETTER 
	Point3D const& getLeftBottom();
	Point3D const& getLeftTop();
	Point3D const& getRightTop();
	int const& getResolution();

private:
Point3D leftBottom,leftTop;
Point3D *rightBottom,rightTop;
int resolution;

};

#endif