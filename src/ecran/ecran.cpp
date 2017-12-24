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

double Ecran::calcHeight()
{
	vec3D h(leftTop, leftBottom);
	return h.getNorm();
}

double Ecran::calcLength()
{
	vec3D l(leftTop, rightTop);
	return l.getNorm();
}

double Ecran::calcVerticalResolution(){

	double length = calcLength(),
		   height = calcHeight(),
		   ratio = double(HResolution)/length;
		   
	return int(height*ratio);
}

Point3D Ecran::FindRightBottom(Point3D topL,Point3D topR, Point3D botL){

	double xCoor = topR.getXCoor() - topL.getXCoor() + botL.getXCoor();
	double yCoor = topR.getYCoor() - topL.getYCoor() + botL.getYCoor();
	double zCoor = topR.getZCoor() - topL.getZCoor() + botL.getZCoor();
	
	return Point3D(xCoor, yCoor, zCoor);
}

Point3D Ecran::calcPixelLocation(unsigned int pixelVPos, unsigned int pixelHPos)
{
	if(pixelHPos < this->HResolution && pixelVPos < this->VResolution)
	{
		vec3D vStep(leftTop, leftBottom),	//Espace entre deux pixels consecutifs sur la meme colonne (a diviser par VResolution
			  hStep(leftTop, rightTop);		//Espace entre deux pixels consecutifs sur la meme ligne (a diviser par HResolution
			  
		vStep = vStep.times(1.d/double(VResolution));
		hStep = hStep.times(1.d/double(HResolution));
			   
		double pixelLocationX = leftTop.getXCoor() + pixelVPos*vStep.getXCoor() + pixelHPos*hStep.getXCoor(),
			   pixelLocationY = leftTop.getYCoor() + pixelVPos*vStep.getYCoor() + pixelHPos*hStep.getYCoor(),
			   pixelLocationZ = leftTop.getZCoor() + pixelVPos*vStep.getZCoor() + pixelHPos*hStep.getZCoor();
			   
		return Point3D(pixelLocationX, pixelLocationY, pixelLocationZ);
	}
	else return Point3D();//Exception mieux !!!!!!!!!!!!!!!
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

unsigned int const& Ecran::getHorizontalResolution(){

	return this->HResolution;
}

unsigned int const& Ecran::getVerticalResolution(){

	return this->VResolution;
}
