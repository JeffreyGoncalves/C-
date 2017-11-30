#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>

using namespace std;

/* Ce fichier permet de recuperer les informations d'un fichier separes par
 * les caracteres ' ', ':' et ','. En outre, il pourra etre integre dans le
 * controlleur du projet afin de parser correctement les informations dans les
 * bons objets.
 * D'ailleurs merci stackOverflow pour la fonction parse !*/

//Fonction séparant les mots de s selon delimiters (liste de caracteres delimiteurs)
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

void parseFile(char* filename)
{
	//Initialisation
	vector<string> tokens;
	ifstream fileToParse;
	fileToParse.open(filename, ios::in);
	
	//Lecture du fichier s'il existe
	if(fileToParse.is_open())
	{
		string currentLine;
		int state = 0;
		
		while(!fileToParse.eof())
		{
			getline(fileToParse, currentLine);
			//Identification de la ligne
			//# : ignore jusqu'a l'apparition d'un \n
			//1ère ligne : position camera
			//2ème ligne : position coin supérieur gauche écran
			//3ème ligne : position coin supérieur droit écran 
			//4ème ligne : position coin inférieur gauche écran
			//5ème ligne : résolution horizontale de l’écran (la résolution verticale se calcule à partir des coordonnées des coins de l’écran)
			//6ème ligne : position source lumineuse suivie de sa couleur RGB 
			//7ème ligne : couleur fond
			//8ème ligne et plus : position des objets de la scène, centre de la sphère, son rayon, sa couleur en RGB, son indice de reflexion
			
			//On remplacera les cout par des operations de parsage (type atoi, etc...)
			//et on retournera une erreur si ce qui est attendu ne correspond pas a
			//ce qui a ete transmis.
			
			//Ne rien faire si c'est un commentaire commencant par #
			//ou une ligne vide
			if(!(currentLine[0] == '#') && currentLine.compare(""))
			{
				tokens = split(currentLine, " :,");
				
				//Purement pour voir si tout fonctionne
				for(unsigned int i=0; i<tokens.size(); i++)
					cout << tokens[i] << endl;
				///////////////////////////////////////
				
				switch(state)
				{
					case 0:
						cout << state << endl;
						cout << "" << endl;
						state++;
						break;
					case 1:
						cout << state << endl;
						cout << "" << endl;
						state++;
						break;
					case 2:
						cout << state << endl;
						cout << "" << endl;
						state++;
						break;
					case 3:
						cout << state << endl;
						cout << "" << endl;
						state++;
						break;
					case 4:
						cout << state << endl;
						cout << "" << endl;
						state++;
						break;
					case 5:
						cout << state << endl;
						cout << "" << endl;
						state++;
						break;
					case 6:
						cout << state << endl;
						cout << "" << endl;
						state++;
						break;
					case 7:
						cout << state << endl;
						cout << "" << endl;
						break;
					default :
						break;
				}
			}
		}
	}
	else cerr << "Erreur : le fichier n'existe pas ou est corrompu..." << endl;
}

int main(int argc, char** argv)
{
	if(argc >= 2)
		parseFile(argv[1]);
		
	else cout << "Format d'entree : ./parsing nomFicherAParser" << endl;
	
	return 0; 
}
