#include "Scene.h"

Scene::Scene() : sceneObjects(), backgroundColor(0, 0, 0) {}

Scene::Scene(Color c) : sceneObjects()
{
	backgroundColor = c;
}

Scene::~Scene()
{
	for(int i=0; i<sceneObjects.size(); i++)
	{
		delete sceneObjects[i];
	}
}

void Scene::addObject(Object3D *o)
{
	sceneObjects.push_back(o);
}

/*bool Scene::removeObject(Object3D *o)
{
	for(int i=0; i<sceneObjects.size(); i++)
	{
		if(o == sceneObjects[i])
		{
			sceneObjects.erase(sceneObjects.begin() + i);
			return true;
		}
	}
	return false;
}*/

/*bool Scene::removeObject(int i)
{
	if(i >= 0 && i<sceneObjects.size())
	{
		Object3D *o = sceneObjects[i];
		sceneObjects.erase(std::remove(sceneObjects.begin()+i), sceneObjects.end());

		delete o;
		return true;
	}
	else return false;
}*/

Object3D* Scene::getObject(int i)
{
	return sceneObjects[i];
}

int main()
{
	Object3D *o = new Sphere(1,1,1,5, Color(121, 100, 5), 1),
			 *p = new Sphere(2,2,2,4, Color(155, 1, 2), 1),
			 *q = new Sphere(4,8,9,2, Color(0, 0, 0), 1);
	Scene s;
	s.addObject(o);
	s.addObject(p);
	s.addObject(q);
	
	//s.removeObject(1);
	
	
	std::cout << dynamic_cast<Sphere&>(*(s.getObject(0))) << std::endl;
	std::cout << dynamic_cast<Sphere&>(*(s.getObject(1))) << std::endl;
	std::cout << dynamic_cast<Sphere&>(*(s.getObject(2))) << std::endl;

	return 0;
}
