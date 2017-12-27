#include "Controller.h"

using namespace std;

/* Ce fichier permet de recuperer les informations d'un fichier separes par
 * les caracteres ' ', ':' et ','. En outre, il pourra etre integre dans le
 * controlleur du projet afin de parser correctement les informations dans les
 * bons objets. De plus, il sert aussi à l'ecriture de l'objet
 * D'ailleurs merci stackOverflow pour la fonction parse !*/

vector<string> split(const string &s, string delimiters)
{
   vector<string> tokens;
   string token;
   istringstream tokenStream(s);
  
	while (getline(tokenStream, token))
	{
		size_t prev = 0, pos;
		while ((pos = s.find_first_of(delimiters, prev)) != std::string::npos)
		{
			if (pos > prev)
				tokens.push_back(s.substr(prev, pos-prev));
			prev = pos+1;
		}
		if (prev < s.length())
			tokens.push_back(s.substr(prev, std::string::npos));
	}
   
   return tokens;
}

Controller::Controller(string filename)
{
	this->picture = NULL;
	
	//Initialisation
	vector<string> tokens;
	ifstream fileToParse;
	fileToParse.open(filename.c_str(), ios::in);
	bool isValid = true;
	
	//Objets temporaires
	Camera cam;
	Point3D topL, topR, botL;
	double doubleTemp[10];
	int intTemp[3];
	
	//Lecture du fichier s'il existe
	if(fileToParse.is_open())
	{
		string currentLine;
		int state = 0;
		
		while(!fileToParse.eof() && isValid)
		{
			getline(fileToParse, currentLine);
			//Identification de la ligne
			//# : ignore jusqu'a l'apparition d'un \n
			//1ère ligne : position camera
			//2ème ligne : position coin supérieur gauche écran
			//3ème ligne : position coin supérieur droit écran 
			//4ème ligne : position coin inférieur gauche écran
			//5ème ligne : résolution horizontale de l’écran (la résolution verticale se calcule à partir des coordonnées des coins de l’écran)
			//6ème ligne : couleur fond
			//7ème ligne : position source lumineuse suivie de sa couleur RGB 
			//8ème ligne et plus : position des objets de la scène, centre de la sphère, son rayon, sa couleur en RGB, son indice de reflexion
			
			//On remplacera les cout par des operations de parsage (type atoi, etc...)
			//et on retournera une erreur si ce qui est attendu ne correspond pas a
			//ce qui a ete transmis.
			
			//Ne rien faire si c'est un commentaire commencant par #
			//ou une ligne vide
			if(!(currentLine[0] == '#') && currentLine.compare(""))
			{
				tokens = split(currentLine, " :,");
				switch(state)
				{
					case 0:
					///////////POSITION CAMERA/////////////
						if(tokens.size() == 3 && istringstream(tokens[0]) >> doubleTemp[0] && 
												 istringstream(tokens[1]) >> doubleTemp[1] && 
												 istringstream(tokens[2]) >> doubleTemp[2])
						{
							cam = Camera(doubleTemp[0], doubleTemp[1], doubleTemp[2]);
							state++;
						}
						else isValid = false;
						break;
					///////////////////////////////////////
					case 1:
					///////////Position point superieur gauche ecran///////////
						if(tokens.size() == 3 && istringstream(tokens[0]) >> doubleTemp[0] && 
												 istringstream(tokens[1]) >> doubleTemp[1] && 
												 istringstream(tokens[2]) >> doubleTemp[2])
						{
							topL = Point3D(doubleTemp[0], doubleTemp[1], doubleTemp[2]);
							state++;
						}
						else isValid = false;
						break;
					///////////////////////////////////////////////////////////
					case 2:
					///////////Position point superieur droite ecran///////////
						if(tokens.size() == 3 && istringstream(tokens[0]) >> doubleTemp[0] && 
												 istringstream(tokens[1]) >> doubleTemp[1] && 
												 istringstream(tokens[2]) >> doubleTemp[2])
						{
							topR = Point3D(doubleTemp[0], doubleTemp[1], doubleTemp[2]);
							state++;
						}
						else isValid = false;
						break;
					///////////////////////////////////////////////////////////
					case 3:
					///////////Position point inferieur gauche ecran///////////
						if(tokens.size() == 3 && istringstream(tokens[0]) >> doubleTemp[0] && 
												 istringstream(tokens[1]) >> doubleTemp[1] && 
												 istringstream(tokens[2]) >> doubleTemp[2])
						{
							botL = Point3D(doubleTemp[0], doubleTemp[1], doubleTemp[2]);
							state++;
						}
						else isValid = false;
						break;
					///////////////////////////////////////////////////////////
					case 4:
					///////////Resolution horizontale + creation scene///////////
						if(tokens.size() == 1 && istringstream(tokens[0]) >> intTemp[0])
						{
							Ecran e(topL, topR, botL, intTemp[0]);
							actualScene = new Scene(cam, e);
							state++;
						}
						else isValid = false;
						break;
					///////////////////////////////////////////////////////////
					case 5:
					///////////		couleur du fond de la scene		///////////
						if(tokens.size() == 3 && istringstream(tokens[0]) >> intTemp[0] && 
												 istringstream(tokens[1]) >> intTemp[1] && 
												 istringstream(tokens[2]) >> intTemp[2])
						{
							actualScene->setBackgroundColor(Color(intTemp[0], intTemp[1], intTemp[2]));
							state++;
						}
						else isValid = false;
						break;
					///////////////////////////////////////////////////////////
					case 6:
					///////////		Ajout d'une lumiere				///////////
						if(tokens.size() == 6 && istringstream(tokens[0]) >> doubleTemp[0] && 
												 istringstream(tokens[1]) >> doubleTemp[1] && 
												 istringstream(tokens[2]) >> doubleTemp[2] &&
												 istringstream(tokens[3]) >> intTemp[0] &&
												 istringstream(tokens[4]) >> intTemp[1] &&
												 istringstream(tokens[5]) >> intTemp[2])
						{
							actualScene->addLightSource(new Source(Point3D(doubleTemp[0], doubleTemp[1], doubleTemp[2]), 
																   Color(intTemp[0], intTemp[1], intTemp[2])));
							state++;
						}
						else isValid = false;
						break;
					///////////////////////////////////////////////////////////
					case 7:
					///////////		Ajout d'une sphere			///////////
						if(tokens.size() >= 1 && !(tokens[0].compare("sphere")))
						{
							if(tokens.size() == 9 && istringstream(tokens[1]) >> doubleTemp[0] && 
												 istringstream(tokens[2]) >> doubleTemp[1] && 
												 istringstream(tokens[3]) >> doubleTemp[2] &&
												 istringstream(tokens[4]) >> doubleTemp[3] &&
												 istringstream(tokens[5]) >> intTemp[0] &&
												 istringstream(tokens[6]) >> intTemp[1] &&
												 istringstream(tokens[7]) >> intTemp[2] && 
												 istringstream(tokens[8]) >> doubleTemp[4])
							{
								actualScene->addObject(new Sphere(doubleTemp[0], doubleTemp[1], doubleTemp[2], doubleTemp[3], Color(intTemp[0], intTemp[1], intTemp[2]), doubleTemp[4], 0.f));
							}
						}
						///////////		Ajout d'un triangle		///////////
						else if(tokens.size() >= 1 && !(tokens[0].compare("triangle")))
						{
							if(tokens.size() == 14 && istringstream(tokens[1]) >> doubleTemp[0] && 
												 istringstream(tokens[2]) >> doubleTemp[1] && 
												 istringstream(tokens[3]) >> doubleTemp[2] &&
												 istringstream(tokens[4]) >> doubleTemp[3] &&
												 istringstream(tokens[5]) >> doubleTemp[4] &&
												 istringstream(tokens[6]) >> doubleTemp[5] &&
												 istringstream(tokens[7]) >> doubleTemp[6] && 
												 istringstream(tokens[8]) >> doubleTemp[7] &&
												 istringstream(tokens[9]) >> doubleTemp[8] && 
												 istringstream(tokens[10]) >> intTemp[0] && 
												 istringstream(tokens[11]) >> intTemp[1] &&
												 istringstream(tokens[12]) >> intTemp[2] &&
												 istringstream(tokens[13]) >> doubleTemp[9])
							{
								actualScene->addObject(new Triangle(Point3D(doubleTemp[0], doubleTemp[1], doubleTemp[2]), 
																	Point3D(doubleTemp[3], doubleTemp[4], doubleTemp[5]), 
																	Point3D(doubleTemp[6], doubleTemp[7], doubleTemp[8]), 
																	Color(intTemp[0], intTemp[1], intTemp[2]), doubleTemp[9], 0));
							}
						}
						else isValid = false;
						break;
					///////////////////////////////////////////////////////////
						
					default :
						break;
				}
				
				if(!isValid)
				{
					actualScene = NULL;
					cerr << "Erreur : le document a parser n'est pas valide..." << endl;
				}
			}
		}
		fileToParse.close();
	}
	else 
	{
		actualScene = NULL;
		cerr << "Erreur : le fichier n'existe pas ou est corrompu..." << endl;
	}
}

Controller::~Controller()
{	
	if(actualScene != NULL)delete actualScene; 
	if(picture != NULL)
	{
		delete[] *picture; 
		delete[] picture;
	}
}

//
bool Controller::ends_with(std::string const &value, std::string const &ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void Controller::printPictureToFile(string filename)
{
	if(!ends_with(filename, ".ppm"))
		filename += ".ppm";
	
	Ecran e = this->actualScene->getEcran();
	
	int length = e.getHorizontalResolution(),
		height = e.getVerticalResolution();
	
	
	ofstream file;
	file.open(filename.c_str(), ios::out);
	file << "P3" << endl;
	file << length << " " << height << endl;
	file << "255" << endl;
	for(int i=0;i<height;i++)
	{
		for(int j=0; j<length; j++)
		{
			file << picture[i][j].getRed() << " ";
			file << picture[i][j].getGreen() << " ";
			file << picture[i][j].getBlue() << " ";
				
			file << " ";
		}
		file << "" << endl;
	}
	
	file.close();
}

void Controller::calcPicture(bool interpolate)
{
	if(actualScene != NULL)
		this->picture = actualScene->calcScenePicture(interpolate);
}
