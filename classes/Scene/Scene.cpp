#include "Scene.h"

Scene::Scene(Camera cam, Ecran e) : sceneObjects(), sceneLights(), backgroundColor(0, 0, 0), 
									sceneCamera(cam), ecran(e) {}

Scene::Scene(Color c, Camera cam, Ecran e) : sceneObjects(), sceneLights(), backgroundColor(c), 
											 sceneCamera(cam), ecran(e) {}

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

Color const& Scene::getBackgroundColor()
{
	return this->backgroundColor;
}

Ecran const& Scene::getEcran()
{
	return this->ecran;
}

//////////////////////////////////////////////////////////
//			Methodes relatives aux Object3D				//
//////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////
//			Methodes de calcul de l'image				//
//////////////////////////////////////////////////////////
Color Scene::calcScenePixel(ray3D ray, Object3D *previousObjectCollided, int nb_rec)
{
	//Initialisation : preparation des pointeurs utilises ici
	Object3D *objectSelected = NULL, *objectCollided = NULL;
	Source *lightSourceSelected = NULL, *lightSourceCollided = NULL;
	Point3D *p = NULL, *objectCollisionPoint = NULL, *lightSourceCollisionPoint = NULL;
	vec3D previous, next;
		 
	
	//On regarde si le rayon en parametre rentre en collision avec une source de lumiere
	//////////////////////////////////////////////////////////
	for(unsigned int i=0; i<sceneLights.size(); i++)
	{
		lightSourceSelected = sceneLights.at(i);
		p = lightSourceSelected->detectCollision(ray);
		if(p != NULL)
		{
			if(lightSourceCollisionPoint != NULL)
			{
				next = vec3D(ray.getOrigin(), *p);
				previous = vec3D(ray.getOrigin(), *lightSourceCollisionPoint);
			}
			
			if(lightSourceCollisionPoint == NULL || (next.getNorm() < previous.getNorm()))
			{
				 delete lightSourceCollisionPoint; 
				 lightSourceCollisionPoint = new Point3D(*p);
				 lightSourceCollided = lightSourceSelected;
			}
		}
		delete p;
	}
	
	//On regarde si le rayon en parametre rentre en collision avec un object3D, si nb_rec != 0
	//////////////////////////////////////////////////////////
	if(nb_rec > 0)
	{
		for(unsigned int i=0; i<sceneObjects.size(); i++)
		{
			objectSelected = sceneObjects.at(i);
			p = objectSelected->detectCollision(ray);
			
			if(p != NULL)
			{
				if(objectCollisionPoint != NULL)
				{
					next = vec3D(ray.getOrigin(), *p);
					previous = vec3D(ray.getOrigin(), *objectCollisionPoint);
				}
				
				if(objectCollisionPoint == NULL || (next.getNorm() < previous.getNorm()))
				{
					delete objectCollisionPoint;
					objectCollisionPoint = new Point3D(*p);
					objectCollided = objectSelected;
				}
			}
			delete p;
		}
	}
	
	//On decide maintenant si on effectue un appel recursif ou un renvoi de couleur apres contact avec une source lumineuse
	//Cas ou la source lumineuse est touchee en premier
	if((lightSourceCollided != NULL && objectCollided == NULL) ||
	   (lightSourceCollided != NULL && objectCollided != NULL && vec3D(ray.getOrigin(), *lightSourceCollisionPoint).getNorm() < vec3D(ray.getOrigin(), *objectCollisionPoint).getNorm()))
	{
		delete lightSourceCollisionPoint;
		delete objectCollisionPoint;
		
		if(previousObjectCollided == NULL)
			return lightSourceCollided->getSourceColor();
		else
		{
			//Couleur renvoyee
			Color sourceColor = lightSourceCollided->getSourceColor();
			Color previousObjectColor = previousObjectCollided->getObjectColor();
			
			vec3D rayNorm = ray.getRayDirection();
			rayNorm = rayNorm.normalize();
			
			double cosAlpha = sqrt(pow(previousObjectCollided->calcNormToPoint(ray.getOrigin()).dot(rayNorm), 2));
			
			double colorR = double(sourceColor.getRed()) * double(previousObjectColor.getRed()) * cosAlpha / 255.d,
				   colorG = double(sourceColor.getGreen()) * double(previousObjectColor.getGreen()) * cosAlpha / 255.d,
				   colorB = double(sourceColor.getBlue()) * double(previousObjectColor.getBlue()) * cosAlpha / 255.d;
				   
			return Color(colorR, colorG, colorB);
		}
	}
	
	//Cas ou aucune source lumineuse n'est touchee en premier
	else
	{
		//Un object3D est touche par le rayon et le nombre de recursions autorisees est superieur strictement a 0
		if(objectCollided != NULL && nb_rec > 0)
		{
			Point3D objCollisionPoint(*objectCollisionPoint);
			delete objectCollisionPoint;
			delete lightSourceCollisionPoint;
			
			ray3D newRay = objectCollided->calcReflexionRay(objCollisionPoint, ray);
			return calcScenePixel(newRay, objectCollided, nb_rec-1);
		}
		else if(previousObjectCollided == NULL)
			return this->getBackgroundColor();
		else return Color(0,0,0);
	}
}

Color** Scene::calcScenePicture()
{
	//Initialisation
	unsigned int hRes = this->ecran.getHorizontalResolution(),
				 vRes = this->ecran.getVerticalResolution();
	
	//Creation du tableau representant l'image
	Color **picture = new Color*[vRes];
	*picture = new Color[vRes * hRes];
	
	for(unsigned int i=1; i<vRes; i++)
		picture[i] = picture[i-1] + hRes;
		
	//Point3D stockant la position du pixel a calculer dans la scene
	Point3D pixelPoint,
			cameraPos = this->sceneCamera.getCameraPosition();
	//////////////////////////////////////////
	
	for(unsigned int i=0; i<vRes; i++)
	{
		for(unsigned int j=0; j<hRes; j++)
		{
			pixelPoint = this->ecran.calcPixelLocation(i, j);
			ray3D startRay(cameraPos, vec3D(cameraPos, pixelPoint));
			picture[i][j] = calcScenePixel(startRay, NULL, 1);
		}
	}
	
	return picture;
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
