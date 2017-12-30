#include "tPyramid.h"

TPyramid::TPyramid(Point3D A, Point3D B, Point3D C, Point3D topPoint, Color color, float ref, float a, float refrac) : Object3D(color, ref, a, refrac)
{
	this->P1 = A;
	this->P2 = B;
	this->P3 = C;
	this->PTop = topPoint;
	
	//Base
	Triangle base(P1,P2,P3, color, ref, a, refrac);
	this->listTriangle[0] = base;
	//Cotes
	Triangle cote1(P1, P2, PTop, color, ref, a, refrac);
	this->listTriangle[1] = cote1;
	Triangle cote2(P2, P3, PTop, color, ref, a, refrac);
	this->listTriangle[2] = cote2;
	Triangle cote3(P3, P1, PTop, color, ref, a, refrac);
	this->listTriangle[3] = cote3;
}

Point3D* TPyramid::detectCollision(ray3D ray)
{
	//Pour chaque triangle de la pyramide, on regarde les points d'impact du rayon ray
	Point3D* listPoints[4];
	for(int i=0; i<4; i++)
		listPoints[i] = listTriangle[i].detectCollision(ray);
		
	//On compare les distances entre differents points de collision, on prend celui avec la distance la plus faible
	Point3D *pointIntersect = NULL;
	double distanceMin = 0;
	for(int i=0; i<4; i++)
	{
		if(listPoints[i] != NULL)
		{
			vec3D vecOI(ray.getOrigin(), *listPoints[i]);
			double distOI = vecOI.getNorm();
			
			//Test de distance et suppression si besoin
			//Premier point a intersecter ou point selectionne meilleur
			if(pointIntersect == NULL || (pointIntersect != NULL && distanceMin > distOI))
			{
				if(pointIntersect != NULL) delete pointIntersect;	//Suppression des points inutiles
				pointIntersect = listPoints[i];
				distanceMin = distOI;
			}
			//Autre cas
			else 
				delete listPoints[i];								//Suppression des points inutiles
		}	
	}
	
	return pointIntersect;
}

vec3D TPyramid::calcNormToPoint(Point3D p)
{
	vec3D simpleVec(1,1,1);
	ray3D ray(p, simpleVec), rayOpposite(p, simpleVec.times(-1));
	
	Point3D* listPoints[4];
	double dists[4];
	for(int i=0;i<4;i++)
	{
		listPoints[i] = this->listTriangle[i].detectCollision(ray);
		if(listPoints[i] == NULL) listPoints[i] = this->listTriangle[i].detectCollision(rayOpposite);
		
		//On regarde si listPoints[i] n'est pas NULL.
		//S'il ne l'est pas, on calcule la distance PPoint et on l'enregistre pour plus tard
		if(listPoints[i] != NULL)
		{
			vec3D vec(p, *listPoints[i]);
			dists[i] = vec.getNorm();
		}
		else dists[i] = -1;
			
	}
	
	//Suppression des points : ils sont inutiles ici
	for(int i=0; i<4; i++)
		if(listPoints[i] != NULL) delete listPoints[i];
	
	//On regarde l'appartenance au triangle
	double actualDist = -1;
	int triangleID = -1;
	for(int i=0; i<4; i++)
	{
		if(dists[i] != -1)
		{
			if(actualDist == -1 || (actualDist != -1 && actualDist > dists[i]) )
			{
				actualDist = dists[i];
				triangleID = i;
			}
		}
	}
	
	//Cas echec : arrive quand le point concerne est au niveau d'une pointe de pyramide
	if(triangleID == -1)
	{
		return vec3D(1,1,1);
	}
	else return this->listTriangle[triangleID].calcNormToPoint(p);
}
