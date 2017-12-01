#include <iostream>
#include <cstdio>
#include "color.h"

class Sphere
{
int centerx,centery, centerz; // coordonnées du centre de la sphère
int radius;					  // rayon
Color rgb; 	  				  // niveaux RGB
float reflexion;			  // indice de réflexion
public:
	Sphere(int x,int y, int z, int r, Color C, float ref);
	Sphere();
	void setCenter(int x, int y , int z);
	
};