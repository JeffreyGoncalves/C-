#include "Scene.h"

Scene::Scene() : sceneObjects(), backgroundColor(0, 0, 0) {}

Scene::Scene(Color c) : sceneObjects()
{
	this->backgroundColor = c;
}

Scene::~Scene()
{
	for(unsigned int i=0; i<sceneObjects.size(); i++)
	{
		delete sceneObjects[i];
	}
	
	for(unsigned int i=0; i<sceneLights.size(); i++)
	{
		delete sceneLights[i];
	}
}

void Scene::addObject(Object3D *o)
{
	this->sceneObjects.push_back(o);
}

bool Scene::removeObject(Object3D *o)
{
	sceneObjects.erase(std::remove(sceneObjects.begin(), sceneObjects.end(), o), sceneObjects.end());
	return false;
}

bool Scene::removeObject(unsigned int i)
{
	if(i >= 0 && i<sceneObjects.size())
	{
		Object3D *o = sceneObjects[i];
		sceneObjects.erase(std::remove(sceneObjects.begin(), sceneObjects.end(), sceneObjects[i]), sceneObjects.end());

		delete o;
		return true;
	}
	else return false;
}

Object3D* const Scene::getObject(int i)
{
	return sceneObjects[i];
}

void Scene::setBackgroundColor(Color newBackColor)
{
	this->backgroundColor = newBackColor;
}

void Scene::setCamera(Camera newCamera)
{
	this->sceneCamera = newCamera;
}

void Scene::addLightSource(Source *newLight)
{
	this->sceneLights.push_back(newLight);
}

Source* const Scene::getLightSource(int i)
{
	return sceneLights[i];
}

/*int main()
{
	Object3D *o = new Sphere(1,1,1,5, Color(121, 100, 5), 1),
			 *p = new Sphere(2,2,2,4, Color(155, 1, 2), 1),
			 *q = new Sphere(4,8,9,2, Color(0, 0, 0), 1);
	Scene s;
	s.addObject(o);
	s.addObject(p);
	s.addObject(q);
	
	s.removeObject(o);
	s.removeObject(p);
	s.removeObject(q);
	
	
	std::cout << dynamic_cast<Sphere&>(*(s.getObject(0))) << std::endl;
	std::cout << dynamic_cast<Sphere&>(*(s.getObject(1))) << std::endl;
	std::cout << dynamic_cast<Sphere&>(*(s.getObject(2))) << std::endl;

	return 0;
}*/
