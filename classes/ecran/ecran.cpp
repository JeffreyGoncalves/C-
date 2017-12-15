#include "ecran.h"

////////CONSTRUCTEUR////////
Ecran::Ecran(Point3D topL,Point3D topR, Point3D botL,int r){

	leftTop=topL;
	leftBottom=botL;
	rightTop=topR;
    FindRightBottom(topL,topR,botL);
	resolution = r;
}

double Ecran::getPixelHeight(){

	double height=0;
	double longueur = rightTop.getXCoor() - leftTop.getXCoor();
	double rapport = resolution / longueur;
	height = longueur * rapport;

	return height;
}

void Ecran::FindRightBottom(Point3D topL,Point3D topR, Point3D botL){

	rightBottom = new Point3D(); 
	double xCoor = topR.getXCoor() - topL.getXCoor() + botL.getXCoor();
	double yCoor = topR.getYCoor() - topL.getYCoor() + botL.getYCoor();
	double zCoor = topR.getZCoor() - topL.getZCoor() + botL.getZCoor();
	rightBottom->setPoint(xCoor,yCoor,zCoor);
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

int const& Ecran::getResolution(){

	return this->resolution;
}