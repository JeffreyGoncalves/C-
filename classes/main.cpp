#include <iostream>
#include <cstdio>
//#include <SDL2/SDL.h>

#include "color.h"
#include "Object3D.h"
#include "sphere.h"
#include "ray3D.h"
#include "Point3D.h"
#include "vec3D.h"

using namespace std;

int main(int arc, char** argv)
{
	vec3D v(1.d,2.d,0.d);
	Point3D p(0,0,10);
	Sphere s(0, 0, 0, 5, Color(255, 0, 0), 1);
	cout << "Le vecteur v a pour valeurs " << v << endl;
	cout << "La norme de v est egale a " << v.getNorm() << endl;
	cout << "v normalise a pours valeurs " << v.normalize() << endl;
	cout << "La norme de v est egale a " << v.normalize().getNorm() << endl;
	cout << "Le point p a pour valeurs " << p << endl;
	cout << "La sphere s a pour caracteristiques " << s << endl;
	cout << "Le vecteur normal a la sphere s au point " << p << " a pour valeurs " << s.calcNormToPoint(p) << endl;
	
	return 0;
}
