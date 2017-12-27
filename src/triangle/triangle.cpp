#include "triangle.h"

Triangle::Triangle(Point3D A, Point3D B, Point3D C, Color color, float ref, float a) : Object3D(color, ref, a)
{
	//Determination du cote le plus long
	double distAB = vec3D(A,B).getNorm(),
		   distBC = vec3D(B,C).getNorm(),
		   distAC = vec3D(A,C).getNorm();
		   
	if(distAB >= distBC && distAB >= distAC)
	{
		this->P1 = A;
		this->P2 = B;
		this->PExt = C;
	}
	else if(distBC >= distAB && distBC >= distAC)
	{
		this->P1 = B;
		this->P2 = C;
		this->PExt = A;
	}
	else //alors AC est le cote le plus long
	{
		this->P1 = A;
		this->P2 = C;
		this->PExt = B;
	}
	///////////////////////////////////////
	
	//Calcul de alphaP1 et alphaP2
	vec3D P1P2(P1, P2), P1PExt(P1, PExt), P2PExt(P2, PExt);
	if(P1P2.getNorm() != 0)
	{
		if(P1PExt.getNorm() != 0)
			this->alphaP1 = acos( fabs(P1P2.dot(P1PExt)) / (P1P2.getNorm() * P1PExt.getNorm()) );
		else this->alphaP1 = 0;
		
		if(P2PExt.getNorm() != 0)
			this->alphaP2 = acos( fabs(P1P2.dot(P2PExt)) / (P1P2.getNorm() * P2PExt.getNorm()) );
		else this->alphaP2 = 0;
	}
	else
	{
		this->alphaP1 = 0;
		this->alphaP2 = 0;
	}
	///////////////////////////////////////
	
	//Calcul du point D intermediaire nous permettant de contruire le plan ayant pour cote P1P2
	double betaP1 = PI/2 - alphaP1;
	
	vec3D P1D;
	if(P1P2.getNorm() != 0)
		P1D = P1P2.times(P1PExt.getNorm() * sin(betaP1) / P1P2.getNorm());
	
	Point3D D(P1D.getXCoor()+P1.getXCoor() ,P1D.getYCoor()+P1.getYCoor() , P1D.getZCoor()+P1.getZCoor() );
	///////////////////////////////////////
	
	//Calcul intermediare de P3 tel que (P1 P2 P3 P4) soit un rectangle dans l'espace, afin de calculer POrigin
	vec3D DPExt(D, PExt);
	Point3D P3(DPExt.getXCoor()+P2.getXCoor(), DPExt.getYCoor()+P2.getYCoor(), DPExt.getZCoor()+P2.getZCoor());
	this->planOrigin = Point3D( (P1.getXCoor() + P1P2.getXCoor()/2 + DPExt.getXCoor()/2), (P1.getYCoor() + P1P2.getYCoor()/2 + DPExt.getYCoor()/2), (P1.getZCoor() + P1P2.getZCoor()/2 + DPExt.getZCoor()/2) );
	this->P1P2Middle = Point3D( (this->planOrigin.getXCoor() - DPExt.getXCoor()/2), (this->planOrigin.getYCoor() - DPExt.getYCoor()/2), (this->planOrigin.getZCoor() - DPExt.getZCoor()/2));
	///////////////////////////////////////
	
	//Calcul final de a, b, c et d tels que pour P(x,y,z) dans le plan(P1 P2 P3 P4), ax+by+cz+d = 0
	//Calcul d'un vecteur normal au plan
	vec3D nToPlan = P1P2.cross(DPExt);
	this->normalVector = nToPlan.normalize();
	this->a = nToPlan.getXCoor();
	this->b = nToPlan.getYCoor();
	this->c = nToPlan.getZCoor();
	this->d = -(nToPlan.getXCoor()*planOrigin.getXCoor()) -(nToPlan.getYCoor()*planOrigin.getYCoor()) - (nToPlan.getZCoor()*planOrigin.getZCoor());
	//////////////////////////////////////
}

Point3D* Triangle::detectCollision(ray3D ray)
{
	//On trouve d'abord le point intersectant le plan infini sur lequel se trouve le triangle, de la forme 
	//f1*t + f2 = 0 avec f1 = a*xd + b*yd + c*zd et f2 = a*x0 + b*y0 + c*z0 + d
	Point3D rayO = ray.getOrigin();
	vec3D rayD = ray.getRayDirection();
	
	double f1 = this->a * rayD.getXCoor() + this->b * rayD.getYCoor() + this->c * rayD.getZCoor();
	double f2 = this->a * rayO.getXCoor() + this->b * rayO.getYCoor() + this->c * rayO.getZCoor() + d;
	
	double t;
	if(f1 != 0)
		t = -f2/f1;
	else t = 0;
	
	Point3D *P = new Point3D(rayO.getXCoor()+t*rayD.getXCoor(), rayO.getYCoor()+t*rayD.getYCoor(), rayO.getZCoor()+t*rayD.getZCoor());
	//Premier test : t >= 0
	if(t >= 0)
	{
		//Deuxieme test : P doit etre a une certaine distance de l'origine du plan
		vec3D OP(this->planOrigin, *P);
		vec3D PMiddleO(this->P1P2Middle, this->planOrigin);
		vec3D P1PMiddle(this->P1, this->P1P2Middle);
		double alphaT;
		if(OP.getNorm() != 0 && PMiddleO.getNorm() != 0)
			alphaT = acos(fabs(OP.dot(PMiddleO)) / (OP.getNorm() * PMiddleO.getNorm()));
		else alphaT = 0;
		
		double toCompare = 0;
		if(cos(alphaT) != 0 && PMiddleO.getNorm()/cos(alphaT) <= sqrt(pow(PMiddleO.getNorm(), 2) + pow(P1PMiddle.getNorm(), 2)))
			toCompare = PMiddleO.getNorm()/cos(alphaT);
		else if(sin(alphaT) != 0 && P1PMiddle.getNorm()/sin(alphaT) <= sqrt(pow(PMiddleO.getNorm(), 2) + pow(P1PMiddle.getNorm(), 2)))
			toCompare = P1PMiddle.getNorm()/sin(alphaT);
		
		if(OP.getNorm() <= toCompare)
		{
			//Troisieme test : on sait que P est dans le plan P1P2P3P4 et on regarde si P est bien dans le triangle
			vec3D P1P2(this->P1, this->P2),
				  P1P(this->P1, *P),
				  P2P1(this->P2, this->P1),
				  P2P(this->P2, *P);
			
			if(P1P2.getNorm() != 0 && P1P.getNorm() != 0 && P2P1.getNorm() != 0 && P2P.getNorm() != 0)
			{
				if( fabs(P2P1.dot(P1P)) / (P2P1.getNorm() * P1P.getNorm())  > cos(this->alphaP1) &&
					fabs(P1P2.dot(P2P)) / (P1P2.getNorm() * P2P.getNorm())  > cos(this->alphaP2) )
				{
					return P;
				}
			}
		}
	}
	
	//Echec a l'un des trois tests
	delete P;
	return NULL;
}

vec3D Triangle::calcNormToPoint(Point3D p)
{
	return this->normalVector;
}
