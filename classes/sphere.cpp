#include "sphere.h"
 
Sphere::Sphere(float x, float y, float z, float r, Color C, float ref) : Object3D(C, ref), center(x,y,z), radius(r) {}

Sphere::Sphere() : Object3D(), center(), radius(0.f) {}

void Sphere::setCenter(float x, float y, float z){

	Point3D new_center(x,y,z);
	center = new_center;
}

void Sphere::setCenter(Point3D new_center)
{
	center = new_center;
}

//Permet de detecter le contact d'un rayon avec la sphere
Point3D* Sphere::detectCollision(Point3D rayOrigin, Point3D rayDirection)
{
	return NULL;
}
