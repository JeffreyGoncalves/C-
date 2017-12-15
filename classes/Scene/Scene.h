#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <algorithm>
#include "Object3D.h"
#include "sphere.h"
#include "color.h"
#include "source.h"
#include "Camera.h"

class Scene
{
	public :
		Scene();
		Scene(Color c);
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
		
	private :
		std::vector<Object3D*> sceneObjects;
		std::vector<Source*> sceneLights;
		Color backgroundColor;
		Camera sceneCamera;
};

#endif
