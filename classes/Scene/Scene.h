#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Object3D.h"
#include "sphere.h"
#include "color.h"
#include "source.h"
#include "Camera.h"
#include "ecran.h"

class Scene
{
	public :
		Scene(Camera cam, Ecran e);
		Scene(Color c, Camera cam, Ecran e);
		~Scene();
		
		void addObject(Object3D *o);
		bool removeObject(Object3D *o);
		bool removeObject(unsigned int i);
		Object3D* const getObject(int i);
		void setBackgroundColor(Color newBackColor);
		void setCamera(Camera newCamera);
		void addLightSource(Source *newLight);
		Source* const getLightSource(int i);
		//void removeLight(light lightToRemove);
		//void removeLight(int i);
		
		//Getters
		Color const& getBackgroundColor();
		Ecran const& getEcran();
		
		//Static setter for interpolation factor
		void setInterpolationFactor(unsigned int factor){if(factor != 0) interpolationFactor = factor;}
		
		//Methode de calcul d'image
		Color** calcScenePicture(bool interpolate);
		
	private :
		std::vector<Object3D*> sceneObjects;
		std::vector<Source*> sceneLights;
		Color backgroundColor;
		Camera sceneCamera;
		Ecran ecran;
		
		//Methode de calcul d'un pixel, utilise uniquement par calcScenePicture
		Color calcScenePixel(ray3D ray, Object3D *previousObject, int nb_rec);	//nb_rec : nombre de recursions autorises
		
		static const int default_nb_max_recursions = 5;
		static const unsigned int defaultInterpolationFactor = 2;
		
		const int nb_max_recursions;
		unsigned int interpolationFactor;
};

#endif
