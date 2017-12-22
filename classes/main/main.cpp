#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
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
	bool interpolate = false,
		 isValid = true;
	int argRead = 1;
	
	Scene s(Color(100, 100, 100), Camera(100, 100, 0), 
			Ecran(Point3D(90,110,30), Point3D(110, 110, 30), Point3D(90, 90, 30), 2000));
		
	s.addLightSource(new Source(Point3D(200, 200, 0), Color(245, 200, 200)));
	s.addObject(new Sphere(90, 90, 60, 2, Color(250, 0, 0), 1));
	s.addObject(new Sphere(100, 110, 60, 5, Color(0, 250, 0), 1));
	s.addObject(new Sphere(110, 110, 60, 2, Color(0, 0, 250), 0.3));
	s.addObject(new Sphere(110, 110, 70, 2, Color(125, 0, 125), 0));
	
	
	//Lecture des options
	while(argv[argRead] != NULL && !strncmp(argv[argRead], "-", 1))
	{
		if(!strcmp(argv[argRead], "-i"))
		{
			if(!interpolate) {
				interpolate = true;
				argRead++;
				//Cas optionnel : reglage de l'interpolation
				if(atoi(argv[argRead]))
				{
					int newInterpolationFactor = atoi(argv[argRead]);
					if(newInterpolationFactor >= 2)
					{
						s.setInterpolationFactor((unsigned int)(newInterpolationFactor));	
						argRead++;
					}
					else {
						isValid = false;
						break;
					}
				}
			}
			else {
				isValid = false;
				break;
			}
		}
	}
		
	if(argv[argRead] != NULL && isValid)
	{
		Color **tab = s.calcScenePicture(interpolate);
		Ecran e = s.getEcran();
	
		printToFile(argv[argRead], tab, e.getHorizontalResolution(), e.getVerticalResolution());
		
		delete[] *tab;
		delete[] tab;
	}
	else 
	{
		cout << "Utilisation : ./test [options] nomFichier" << endl;
		cout << "Options : -i [int] : interpolate to int factor >= 2 (set to 2 by default) " << endl;
	}
	
	
	return 0;
}
