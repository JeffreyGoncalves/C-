#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <cstdarg>
#include "Object3D.h"
#include "sphere.h"
#include "color.h"

class Scene
{
	public :
		Scene();
		Scene(Color c);
		~Scene();
		
		void addObject(Object3D *o);
		//bool removeObject(Object3D *o);
		//bool removeObject(int i);
		Object3D* getObject(int i);
		
		//void setBackgroundColor(Color newBackColor);
		//void setCamera(camera newCamera);
		//void addLight(light newLight);
		//void removeLight(light lightToRemove);
		//void removeLight(int i);
		
	private :
		std::vector<Object3D*> sceneObjects;
		//std::vector<light> lights;
		Color backgroundColor;
		//camera c;
};

#endif
