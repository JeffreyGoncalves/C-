#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include "Object3D.h"
#include "Point3D.h"
#include "sphere.h"
#include "tPyramid.h"
#include "color.h"
#include "source.h"
#include "Camera.h"
#include "ecran.h"
#include "ray3D.h"
#include "vec3D.h"

class Scene
{
	public :
		Scene(Camera cam, Ecran e);
		Scene(Color c, Camera cam, Ecran e);
		~Scene();
		
		//Gestion des objets
		void addObject(Object3D *o);
		
		//Gestion des lumieres
		void addLightSource(Source *newLight);
		
		//Getters
		Object3D* const getObject(int i);
		Source* const getLightSource(int i);
		Color const& getBackgroundColor();
		Ecran const& getEcran();
		//////////////////////////////////
		
		//Setters
		void setBackgroundColor(Color newBackColor);
		void setCamera(Camera newCamera);
		//////////////////////////////////
		
		//Static setter for interpolation factor
		inline void setInterpolationFactor(unsigned int factor){if(factor != 0) interpolationFactor = factor;}
		inline void setNbMaxRecursions(unsigned int factor){nb_max_recursions = factor;}
		inline void setAmbientLight(Color newAmbientLight){ambientLight = newAmbientLight;}
		
		//Methode de calcul d'image
		Color** calcScenePicture(bool interpolate);
		
	private :
		std::vector<Object3D*> sceneObjects;
		std::vector<Source*> sceneLights;
		Color backgroundColor;
		Camera sceneCamera;
		Ecran ecran;
		
		//Methode de calcul d'un pixel, utilise uniquement par calcScenePicture
		Color calcScenePixel(ray3D ray, Object3D *previousObject, unsigned int nb_rec);	//nb_rec : nombre de recursions autorises
		Color interpolationLoop(unsigned int i, unsigned int j, Ecran screenToInterpolate);
		
		//Constantes statiques : parametres par defaut
		static const int default_nb_max_recursions = 1;					//Nombre maximal de passes pour le calcul de la reflexion speculaire
		static const unsigned int defaultInterpolationFactor = 2;		//Facteur d'interpolation
		static const Color defaultAmbientLight;
		
		//Parametres de la scene
		unsigned int nb_max_recursions;
		unsigned int interpolationFactor;
		Color ambientLight;
};

#endif
