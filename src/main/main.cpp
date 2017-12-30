#include "main.h"

using namespace std;

int main(int argc, char** argv)
{
	bool interpolate = false,
		 nbMaxRecursionsSet = false,
		 isValid = true;
		 
	int argRead = 1,
		interpolationFactor = -1,
		nbMaxRecursion = -1;
	
	//Lecture des options
	while(argv[argRead] != NULL && !strncmp(argv[argRead], "-", 1))
	{
		//////////////////////
		//Option interpolate//
		//////////////////////
		if(!strcmp(argv[argRead], "-i"))
		{
			if(!interpolate) 
			{
				interpolate = true;
				argRead++;
				
				//Cas optionnel : reglage de l'interpolation
				if(argc > argRead)
				{
					int newInterpolationFactor;
					istringstream str(argv[argRead]);
					if(str >> newInterpolationFactor)
					{
						if(newInterpolationFactor >= 2)
						{
							interpolationFactor = newInterpolationFactor;
							argRead++;
						}
						else {
							isValid = false;
							break;
						}
					}
				}
				else
				{
					isValid = false;
					break;
				}
				/////////////////////////////////
			}
			
			else {
				isValid = false;
				break;
			}
		}
		//////////////////////////////////////////////////////////
		
		////////////////////////////////////////
		//Option set specular reflexion passes//
		////////////////////////////////////////
		else if(!strcmp(argv[argRead], "-p"))
		{
			if(!nbMaxRecursionsSet)
			{
				argRead++;
				//Cas optionnel : nombre de passes a calculer
				if(argc > argRead)
				{
					int newNbMaxRec;
					istringstream str(argv[argRead]);
					if(str >> newNbMaxRec)
					{
						nbMaxRecursion = newNbMaxRec;
						argRead++;
					}
				}
				else
				{
					isValid = false;
					break;
				}
			}
			else
			{
				isValid = false;
				break;
			}
		}
		
		//Option erronee
		else
		{
			isValid = false;
			break;
		}
	}
		
	//Tout est valide
	if(argc > argRead+1 && isValid)
	{
		//Parsage du fichier
		Controller controller(argv[argRead++]);
		//Cas valide (fichier correctement parse)
		if(!controller.isSceneNull())
		{
			if(interpolationFactor != -1)
				controller.setInterpolationFactor(interpolationFactor);
			
			if(nbMaxRecursion != -1)
				controller.setNbMaxRecursions(nbMaxRecursion);
		
			//Calcul de l'image
			controller.calcPicture(interpolate);
		
			//Entree des informations dans un fichier
			cout << "Printing picture calculated to file..." << endl;
			controller.printPictureToFile(argv[argRead]);
		}
	}
	else //Message d'aide en cas d'erreur d'entree
	{
		cout << "Usage : ./prog [options] fileToParse pictureName" << endl;
		cout << "Options :" << endl; 
		cout << "-i [int] : interpolate to int factor >= 2 (set to 2 by default) " << endl;
		cout << "-p [int] : change count of specular reflexion passes (set to 1 by default) " << endl;
	}
	
	return 0;
}
