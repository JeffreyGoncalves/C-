#include <iostream>
#include <fstream>
#include <cstdlib>
//#include <SDL2/SDL.h>

#include "Scene.h"
#include "ecran.h"
#include "color.h"
#include "Object3D.h"
#include "sphere.h"
#include "ray3D.h"
#include "Point3D.h"
#include "vec3D.h"

using namespace std;

void printToFile(const string fileToWrite, Color **tab, int length, int height)
{
	ofstream file;
	file.open("testPicture", ios::out);
	file << "P3" << endl;
	file << length << " " << height << endl;
	file << "255" << endl;
	for(int i=0;i<height;i++)
	{
		for(int j=0; j<length; j++)
		{
			file << tab[i][j].getRed() << " ";
			file << tab[i][j].getGreen() << " ";
			file << tab[i][j].getBlue() << " ";
				
			file << " ";
		}
		file << "" << endl;
	}
	
	file.close();
}

int main(int arc, char** argv)
{
	/*vec3D v(1.d,2.d,0.d);
	vec3D w(2, 3, 7), x(7, 5, 1), y(0, 1, 3);
	Point3D p(0,0,10);
	Object3D *o = new Sphere(0, 0, 0, 5, Color(255, 0, 0), 1);
	Sphere *t = dynamic_cast<Sphere*>(o), s = *t; 
	cout << "Le vecteur v a pour valeurs " << v << endl;
	cout << "La norme de v est egale a " << v.getNorm() << endl;
	cout << "v normalise a pours valeurs " << v.normalize() << endl;
	cout << "La norme de v est egale a " << v.normalize().getNorm() << endl;
	cout << "Le point p a pour valeurs " << p << endl;
	cout << "La sphere s a pour caracteristiques " << s << endl;
	cout << "Le vecteur normal a la sphere s au point " << p << " a pour valeurs " << s.calcNormToPoint(p) << endl;
	
	w += x;
	cout << "W a pour valeurs " << w << endl;
	cout << "La somme de x et y donne les valeurs " << x+y << endl;
	
	delete o;*/
	
	Scene s(Color(80, 80, 100), Camera(100, 100, 0), 
			Ecran(Point3D(90,110,30), Point3D(110, 110, 30), Point3D(90, 90, 30), 1200));
		
	s.addLightSource(new Source(Point3D(200, 300, 0), Color(245, 200, 200)));
	s.addObject(new Sphere(90, 90, 60, 7, Color(250, 0, 0), 0.3));
	s.addObject(new Sphere(100, 110, 60, 7, Color(0, 250, 0), 0.3));
	s.addObject(new Sphere(110, 110, 60, 7, Color(0, 250, 0), 0.3));
	
	Color **tab = s.calcScenePicture();
	Ecran e = s.getEcran();
	
	printToFile("testPicture", tab, e.getHorizontalResolution(), e.getVerticalResolution());
	
	delete[] *tab;
	delete[] tab;
	
	return 0;
}
