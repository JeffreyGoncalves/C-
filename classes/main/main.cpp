#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <sstream>
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

bool ends_with(std::string const &value, std::string const &ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void printToFile(string fileToWrite, Color **tab, int length, int height)
{
	if(!ends_with(fileToWrite, ".ppm"))
		fileToWrite += ".ppm";
	
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
		 nbMaxRecursionsSet = false,
		 isValid = true;
	int argRead = 1;
	
	Scene s(Color(5, 5, 5), Camera(100, 100, 0), 
			Ecran(Point3D(110,110,30), Point3D(90, 110, 30), Point3D(110, 90, 30), 400));
		
	s.addLightSource(new Source(Point3D(100, 120, 0), Color(255, 255, 255)));
	s.addObject(new Sphere(90, 95, 60, 9, Color(250, 0, 0), 0.6));
	s.addObject(new Sphere(100, 110, 60, 9, Color(0, 250, 0), 0.6));
	s.addObject(new Sphere(110, 95, 60, 9, Color(0, 0, 250), 0.6));
	
	
	//Lecture des options
	while(argv[argRead] != NULL && !strncmp(argv[argRead], "-", 1))
	{
		//////////////////////
		//Option interpolate//
		//////////////////////
		if(!strcmp(argv[argRead], "-i"))
		{
			if(!interpolate) 
			{
				interpolate = true;
				argRead++;
				
				//Cas optionnel : reglage de l'interpolation
				if(argc > argRead)
				{
					int newInterpolationFactor;
					istringstream str(argv[argRead]);
					if(str >> newInterpolationFactor)
					{
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
				else
				{
					isValid = false;
					break;
				}
				/////////////////////////////////
			}
			
			else {
				isValid = false;
				break;
			}
		}
		//////////////////////////////////////////////////////////
		
		////////////////////////////////////////
		//Option set specular reflexion passes//
		////////////////////////////////////////
		else if(!strcmp(argv[argRead], "-p"))
		{
			if(!nbMaxRecursionsSet)
			{
				argRead++;
				//Cas optionnel : nombre de passes a calculer
				if(argc > argRead)
				{
					int newNbMaxRec;
					istringstream str(argv[argRead]);
					if(str >> newNbMaxRec)
					{
						s.setNbMaxRecursions((unsigned int)(newNbMaxRec));	
						argRead++;
					}
				}
				else
				{
					isValid = false;
					break;
				}
			}
			else
			{
				isValid = false;
				break;
			}
		}
		
		//Option erronee
		else
		{
			isValid = false;
			break;
		}
	}
		
	if(argv[argRead] != NULL && isValid)
	{
		//Calcul de l'image
		cout << "Calculating picture..." << endl;
		Color **tab = s.calcScenePicture(interpolate);
		Ecran e = s.getEcran();
		
		//Entree des informations dans un fichier
		cout << "Printing picture calculated to file..." << endl;
		printToFile(argv[argRead], tab, e.getHorizontalResolution(), e.getVerticalResolution());
		
		delete[] *tab;
		delete[] tab;
	}
	else //Message d'aide en cas d'erreur d'entree
	{
		cout << "Utilisation : ./test [options] nomFichier" << endl;
		cout << "Options :" << endl; 
		cout << "-i [int] : interpolate to int factor >= 2 (set to 2 by default) " << endl;
		cout << "-p [int] : change count of specular reflexion passes (set to 3 by default) " << endl;
	}
	
	return 0;
}
