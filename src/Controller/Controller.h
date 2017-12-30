#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>

#include "Scene.h"
#include "Object3D.h"
#include "Point3D.h"
#include "ray3D.h"
#include "vec3D.h"
#include "color.h"
#include "source.h"
#include "Camera.h"
#include "ecran.h"

class Controller
{
	public : 
		//Constructeurs
		Controller(std::string filename);
		~Controller();
		////////////////
		
		//Getteurs
		inline bool isSceneNull() {return (actualScene == NULL);}
		////////////////
		
		//Interpolation et nombres de passes (reflexion speculative)
		inline void setInterpolationFactor(unsigned int factor){if(actualScene != NULL) actualScene->setInterpolationFactor(factor);}
		inline void setNbMaxRecursions(unsigned int factor){if(actualScene != NULL) actualScene->setNbMaxRecursions(factor);}
		
		
		void calcPicture(bool interpolate);
		void printPictureToFile(std::string filename);
		
	private :
		Scene *actualScene;
		Color **picture;
		
		bool ends_with(std::string const &value, std::string const &ending);
};

#endif
