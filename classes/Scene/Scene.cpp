#include "Scene.h"

Scene::Scene(Camera cam, Ecran e) : sceneObjects(), sceneLights(), backgroundColor(0, 0, 0), 
									sceneCamera(cam), ecran(e), nb_max_recursions(Scene::default_nb_max_recursions),
									interpolationFactor(Scene::defaultInterpolationFactor) {}

Scene::Scene(Color c, Camera cam, Ecran e) : sceneObjects(), sceneLights(), backgroundColor(c), 
											 sceneCamera(cam), ecran(e), nb_max_recursions(Scene::default_nb_max_recursions),
											 interpolationFactor(Scene::defaultInterpolationFactor) {}

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
Color Scene::calcScenePixel(ray3D ray, Object3D *previousObject, unsigned int nb_rec)
{
	//Initialisation : preparation des pointeurs utilises ici
	Object3D *objectSelected = NULL, *objectCollided = NULL;
	Point3D *p = NULL, *objectCollisionPoint = NULL;
	vec3D previous, next;
	bool isIlluminated = true;
		 
	
	//On regarde si le rayon en parametre rentre en collision avec un objet
	//////////////////////////////////////////////////////////
	for(unsigned int i=0; i<sceneObjects.size(); i++)
	{
		objectSelected = sceneObjects.at(i);
		if(objectSelected != previousObject)
		{
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
	
	//On decide maintenant si on effectue un appel recursif ou un renvoi de couleur apres contact avec un object3D
	if(nb_rec == 0 && objectCollisionPoint == NULL)
	{
		//Renvoie la couleur de fond, en fonction de la presence d'une source lumineuse proche
		//De base : return this->getBackgroundColor()
		Color c = this->getBackgroundColor(),
			  sourceColor = this->sceneLights.at(0)->getSourceColor();
				  
		vec3D cameraToLightVec(this->sceneCamera.getCameraPosition(), this->sceneLights.at(0)->getSourceLocation()),
			  cameraToPixelVec(ray.getRayDirection());
		cameraToLightVec = cameraToLightVec.normalize();
		cameraToPixelVec = cameraToPixelVec.normalize();
		
		double distanceToLight = vec3D(ray.getOrigin(), this->sceneLights.at(0)->getSourceLocation()).getNorm();
		
		double cosT = cameraToLightVec.dot(cameraToPixelVec),
			   newR = double(sourceColor.getRed()) * double(c.getRed()) / 255.d,
			   newG = double(sourceColor.getGreen()) * double(c.getGreen()) / 255.d,
			   newB = double(sourceColor.getBlue()) * double(c.getBlue()) / 255.d;
		
		return Color(int(newR), int(newG), int(newB)).times(sqrt(pow(cosT,2)));
	}
	
	else if(objectCollided != NULL)
	{
		Source *s = sceneLights.at(0);
		ray3D rayObjectToLight(*objectCollisionPoint, vec3D(*objectCollisionPoint, s->getSourceLocation()));
		ray3D rayReflected = objectCollided->calcReflexionRay(*objectCollisionPoint, ray);
		//On verifie qu'aucun objet ne fait obstacle ici
		for(unsigned int i=0; i<sceneObjects.size(); i++)
		{
			objectSelected = sceneObjects.at(i);
			p = objectSelected->detectCollision(rayObjectToLight);
			if(p != NULL)
			{
				vec3D obstacle(*objectCollisionPoint, *p),
					  objectToLightVec = rayObjectToLight.getRayDirection();
				if(obstacle.getNorm() >= objectToLightVec.getNorm())
				{
					isIlluminated = false;
					break;
				}
				delete p;
			}
		}
		///////////////////////////////////////////////
		
		if(isIlluminated && nb_rec <= nb_max_recursions)
		{
			//Couleur renvoyee
			Color sourceColor = s->getSourceColor();
			Color objectColor = objectCollided->getObjectColor();
			
			vec3D rayNorm(*objectCollisionPoint, s->getSourceLocation());
			rayNorm = rayNorm.normalize();
			
			double cosAlpha = objectCollided->calcNormToPoint(*objectCollisionPoint).dot(rayNorm),
				   reflexFactor = 1.d - double(objectCollided->getObjectReflexionFactor());
				   
			double colorR, colorB, colorG;
			
			cosAlpha = abs(cosAlpha);
			colorR = reflexFactor * double(sourceColor.getRed()) * double(objectColor.getRed()) * cosAlpha / 255.d, 
			colorG = reflexFactor * double(sourceColor.getGreen()) * double(objectColor.getGreen()) * cosAlpha / 255.d,
			colorB = reflexFactor * double(sourceColor.getBlue()) * double(objectColor.getBlue()) * cosAlpha / 255.d;
			
			delete objectCollisionPoint;   
			return Color(colorR, colorG, colorB) + calcScenePixel(rayReflected, objectCollided, nb_rec+1).times(double(objectCollided->getObjectReflexionFactor()));
		}
		else if(nb_rec <= nb_max_recursions)
		{
			delete objectCollisionPoint;
			return calcScenePixel(rayReflected, objectCollided, nb_rec+1).times(double(objectCollided->getObjectReflexionFactor()));
		}
		else
		{
			delete objectCollisionPoint;
			return Color(0,0,0);
		}
	}
	
	else //Cas ou objectCollided == NULL et nb_rec != 0
	{
		delete objectCollisionPoint;
		return Color(0,0,0);//Si nb_rec != 0 && objectCollided == NULL
	}
}

Color** Scene::calcScenePicture(bool interpolate)
{
	//Initialisation
	unsigned int hRes = this->ecran.getHorizontalResolution(),
				 vRes = this->ecran.getVerticalResolution();
	
	//Creation du tableau representant l'image
	Color **picture = new Color*[vRes];
	*picture = new Color[vRes * hRes];
	
	for(unsigned int i=1; i<vRes; i++)
		picture[i] = picture[i-1] + hRes;
		
	//Point3D stockant la position de la camera
	Point3D cameraPos = this->sceneCamera.getCameraPosition();
	//////////////////////////////////////////
	
	//Si on demande l'interpolation
	if(interpolate)
	{
		//Creation de l'ecran a interpoler, et des objets temporaires necessaires
		Ecran screenToInterpolate(this->ecran.getLeftTop(), this->ecran.getRightTop(), this->ecran.getLeftBottom(), hRes*interpolationFactor);
		Point3D pixelPoint[interpolationFactor][interpolationFactor];
		Color pixelColor;
		
		int colorRed = 0, colorGreen = 0, colorBlue = 0;
		
		////////////////////////////////////////
		
		for(unsigned int i=0; i<vRes*interpolationFactor; i += interpolationFactor)
		{
			for(unsigned int j=0; j<hRes*interpolationFactor; j += interpolationFactor)
			{
				//Calcul intermediaire des pixels
				for(unsigned int k=i; k<i+interpolationFactor; k++)
				{
					for(unsigned int l=j; l<j+interpolationFactor; l++)
					{
						pixelPoint[k-i][l-j] = screenToInterpolate.calcPixelLocation(k, l);
						ray3D startRay(cameraPos, vec3D(cameraPos, pixelPoint[k-i][l-j]));
						pixelColor = calcScenePixel(startRay, NULL, 0);
						
						colorRed += pixelColor.getRed();
						colorGreen += pixelColor.getGreen();
						colorBlue += pixelColor.getBlue();
					}
				}
				//////////////////////////////////
				
				//Calcul de la moyenne des couleurs calculees et entree dans le tableau
				colorRed /= (interpolationFactor * interpolationFactor);
				colorBlue /= (interpolationFactor * interpolationFactor);
				colorGreen /= (interpolationFactor * interpolationFactor);
				picture[i/interpolationFactor][j/interpolationFactor] = Color(colorRed, colorGreen, colorBlue);
			}
		}
	}
	
	else
	{
		//Point3D stockant la position du pixel a calculer dans la scene
		Point3D pixelPoint;
		for(unsigned int i=0; i<vRes; i++)
		{
			for(unsigned int j=0; j<hRes; j++)
			{
				pixelPoint = this->ecran.calcPixelLocation(i, j);
				ray3D startRay(cameraPos, vec3D(cameraPos, pixelPoint));
				picture[i][j] = calcScenePixel(startRay, NULL, 0);
			}
		}
	}
	
	return picture;
}
