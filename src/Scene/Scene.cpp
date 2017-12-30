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
		Color c = this->getBackgroundColor();
		
		double logNewR=0, logNewG=0, logNewB=0;
		double newR=0, newG=0, newB=0;
		
		for(unsigned int i=0; i<sceneLights.size(); i++)
		{
			Source *s = sceneLights.at(i);
			
			Color sourceColor = s->getSourceColor();
			vec3D cameraToLightVec(this->sceneCamera.getCameraPosition(), s->getSourceLocation()),
				  cameraToPixelVec(ray.getRayDirection());
				  
			cameraToLightVec = cameraToLightVec.normalize();
			cameraToPixelVec = cameraToPixelVec.normalize();
			
			double cosT = fabs(cameraToLightVec.dot(cameraToPixelVec));
			
			logNewR = double(sourceColor.getRed()) * double(c.getRed()) * cosT / 255.d;
			logNewG = double(sourceColor.getGreen()) * double(c.getGreen()) * cosT / 255.d;
			logNewB = double(sourceColor.getBlue()) * double(c.getBlue()) * cosT / 255.d;
			
			newR += log2(logNewR > 1 ? logNewR : 1);
			newG += log2(logNewG > 1 ? logNewG : 1);
			newB += log2(logNewB > 1 ? logNewB : 1);
		}
				  
		newR = pow(2, newR/double(sceneLights.size()));
		newG = pow(2, newG/double(sceneLights.size()));
		newB = pow(2, newB/double(sceneLights.size()));
		
		
		return Color(int(newR), int(newG), int(newB));
	}
	
	else if(objectCollided != NULL)
	{
		bool isIlluminated [sceneLights.size()];
		int numberOfLightsCollided = 0;
		ray3D rayReflected = objectCollided->calcReflexionRay(*objectCollisionPoint, ray);
		
		//Pour chaque source lumineuse, on regarde si elle contribue a l'illumination de l'objet
		for(unsigned int k=0; k<sceneLights.size(); k++)
		{
			isIlluminated[k] = true;
			Source *s = sceneLights.at(k);
			ray3D rayObjectToLight(*objectCollisionPoint, vec3D(*objectCollisionPoint, s->getSourceLocation()));
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
						isIlluminated[k] = false;
						break;
					}
					delete p;
				}
			}
			if(isIlluminated[k])numberOfLightsCollided++;
		}
		
		///////////////////////////////////////////////
		
		if(numberOfLightsCollided > 0 && nb_rec <= nb_max_recursions)
		{
			Color objectColor = objectCollided->getObjectColor();
			double cosAlpha, reflexFactor;
			double logColorR = 0, logColorG = 0, logColorB = 0;
			double colorR = 0, colorG = 0, colorB = 0;
			
			//Moyenne logarithmique (base 2) des contributions lumineuses
			for(unsigned int i=0; i<sceneLights.size(); i++)
			{
				if(isIlluminated[i])
				{
					Source *s = sceneLights.at(i);
					
					Color actualSourceColor = s->getSourceColor();
					vec3D rayNorm(*objectCollisionPoint, s->getSourceLocation());
				
					rayNorm = rayNorm.normalize();
				
					//Calcul du cosinus et du facteur 1-Reflexion-Transparence
					cosAlpha = fabs(objectCollided->calcNormToPoint(*objectCollisionPoint).dot(rayNorm));
					reflexFactor = fabs(1.d - double(objectCollided->getObjectReflexionFactor()) - double(objectCollided->getObjectAlpha()));
				
					logColorR = reflexFactor * double(actualSourceColor.getRed()) * double(objectColor.getRed()) * cosAlpha / 255.d, 
					logColorG = reflexFactor * double(actualSourceColor.getGreen()) * double(objectColor.getGreen()) * cosAlpha / 255.d,
					logColorB = reflexFactor * double(actualSourceColor.getBlue()) * double(objectColor.getBlue()) * cosAlpha / 255.d;
					
					colorR += log2(logColorR > 1 ? logColorR : 1);
					colorG += log2(logColorG > 1 ? logColorG : 1);
					colorB += log2(logColorB > 1 ? logColorB : 1);
				}
			}
			colorR /= double(numberOfLightsCollided);
			colorG /= double(numberOfLightsCollided);
			colorB /= double(numberOfLightsCollided);
			
			colorR = pow(2, colorR);
			colorG = pow(2, colorG);
			colorB = pow(2, colorB);
			
			
			delete objectCollisionPoint;  
			return Color(colorR, colorG, colorB) + calcScenePixel(rayReflected, objectCollided, nb_rec+1).times(double(objectCollided->getObjectReflexionFactor()))
												 + calcScenePixel(ray, objectCollided, nb_rec+1).times(double(objectCollided->getObjectAlpha()));
		}
		else if(nb_rec <= nb_max_recursions)
		{
			delete objectCollisionPoint;
			return calcScenePixel(rayReflected, objectCollided, nb_rec+1).times(double(objectCollided->getObjectReflexionFactor())) +
				   calcScenePixel(ray, objectCollided, nb_rec+1).times(double(objectCollided->getObjectAlpha()));
		}
		else
		{
			delete objectCollisionPoint;
			return Color(25,25,25);
		}
	}
	
	else //Cas ou objectCollided == NULL et nb_rec != 0
	{
		delete objectCollisionPoint;
		return Color(25,25,25);//Si nb_rec != 0 && objectCollided == NULL
	}
}

Color Scene::interpolationLoop(unsigned int i, unsigned int j, Ecran screenToInterpolate)
{
	Point3D pixelPoint[interpolationFactor][interpolationFactor];
	Point3D cameraPos = this->sceneCamera.getCameraPosition();
	Color pixelColor;
	int colorRed = 0, colorGreen = 0, colorBlue = 0;
	
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
	return Color(colorRed, colorGreen, colorBlue);
}

Color** Scene::calcScenePicture(bool interpolate)
{
	//Initialisation
	unsigned int hRes = this->ecran.getHorizontalResolution(),
				 vRes = this->ecran.getVerticalResolution();		 
	
	//Initialisation du tableau contenant les donnees de l'image
	std::cout << "Initialization of array for entering picture values ..." << std::endl;
	Color **picture = new Color*[vRes];
	*picture = new Color[vRes * hRes];
	
	for(unsigned int i=1; i<vRes; i++)
		picture[i] = picture[i-1] + hRes;
	//////////////////////////////////////////
	
	//Point3D stockant la position de la camera
	Point3D cameraPos = this->sceneCamera.getCameraPosition();
	//////////////////////////////////////////
	
	//Si on demande l'interpolation
	std::cout << "Calculating and entering values in the array ..." << std::endl;
	if(interpolate)
	{
		//Creation de l'ecran a interpoler, et des objets temporaires necessaires
		Ecran screenToInterpolate(this->ecran.getLeftTop(), this->ecran.getRightTop(), this->ecran.getLeftBottom(), hRes*interpolationFactor);
		
		////////////////////////////////////////
		#pragma omp parallel for schedule(dynamic,2) collapse(2) ordered
		for(unsigned int i=0; i<vRes*interpolationFactor; i += interpolationFactor)
		{
			for(unsigned int j=0; j<hRes*interpolationFactor; j += interpolationFactor)
			{
				picture[i/interpolationFactor][j/interpolationFactor] = interpolationLoop(i,j, screenToInterpolate);
			}
		}
	}
	
	else
	{
		//Point3D stockant la position du pixel a calculer dans la scene
		Point3D pixelPoint;
		#pragma omp parallel for schedule(dynamic,2) collapse(2) ordered
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
