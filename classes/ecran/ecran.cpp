#include "ecran.h"

////////CONSTRUCTEUR////////
Ecran::Ecran(Point3D topL,Point3D topR, Point3D botL, int horizontalRes){

	leftTop=topL;
	leftBottom=botL;
	rightTop=topR;
	rightBottom = FindRightBottom(topL,topR,botL);
	HResolution = horizontalRes;
	VResolution = calcVerticalResolution();
}

double Ecran::calcVerticalResolution(){

	vec3D l(leftTop, rightTop),
		  h(leftTop, leftBottom);
	double length = l.getNorm(),
		   height = h.getNorm(),
		   ratio = HResolution/length;
		   
	return height*ratio;
}

Point3D Ecran::FindRightBottom(Point3D topL,Point3D topR, Point3D botL){

	double xCoor = topR.getXCoor() - topL.getXCoor() + botL.getXCoor();
	double yCoor = topR.getYCoor() - topL.getYCoor() + botL.getYCoor();
	double zCoor = topR.getZCoor() - topL.getZCoor() + botL.getZCoor();
	
	return Point3D(xCoor, yCoor, zCoor);
}

//////GETTERS//////
Point3D const& Ecran::getLeftBottom(){

	return this->leftBottom;
}

Point3D const&  Ecran::getLeftTop(){

	return this->leftTop;
}

Point3D const& Ecran::getRightTop(){

	return this->rightTop;
}

int const& Ecran::getHorizontalResolution(){

	return this->HResolution;
}

int const& Ecran::getVerticalResolution(){

	return this->VResolution;
}
