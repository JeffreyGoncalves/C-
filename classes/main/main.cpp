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

void printToFile(string fileToWrite, Color **tab, int length, int height)
{
	ofstream file;
	file.open(fileToWrite.c_str(), ios::out);
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

int main(int argc, char** argv)
{
	Scene s(Color(100, 100, 100), Camera(100, 100, 0), 
			Ecran(Point3D(90,110,30), Point3D(110, 110, 30), Point3D(90, 90, 30), 2000));
		
	s.addLightSource(new Source(Point3D(200, 200, 0), Color(245, 200, 200)));
	s.addObject(new Sphere(90, 90, 60, 2, Color(250, 0, 0), 1));
	s.addObject(new Sphere(100, 110, 60, 5, Color(0, 250, 0), 1));
	s.addObject(new Sphere(110, 110, 60, 2, Color(0, 0, 250), 0.3));
	s.addObject(new Sphere(110, 110, 70, 2, Color(125, 0, 125), 0));
	
	
	if(argc >= 2)
	{
		Color **tab = s.calcScenePicture();
		Ecran e = s.getEcran();
	
		printToFile(argv[1], tab, e.getHorizontalResolution(), e.getVerticalResolution());
		
		delete[] *tab;
		delete[] tab;
	}
	else cout << "Utilisation : ./test nomFichier" << endl;
	
	
	return 0;
}
