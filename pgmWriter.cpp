#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void printToFile(string fileToWrite, int ***tab, int length, int height)
{
	ofstream file;
	file.open(fileToWrite, ios::out);
	file << "P3" << endl;
	file << length << " " << height << endl;
	file << "255" << endl;
	for(int i=0;i<height;i++)
	{
		for(int j=0; j<length; j++)
		{
			for(int k=0; k<3; k++)
				file << tab[i][j][k] << " ";
				
			file << " ";
		}
		file << "" << endl;
	}
	
	file.close();
}

int main(int argc, char **argv)
{
	/*int ***tab = new int**[480];
	for(int i=0; i<480; i++)
	{
		tab[i] = new int*[640];
		for(int j=0; j<640; j++)
			tab[i][j] = new int[3];
	}
	
	for(int i=0;i<480;i++)
		for(int j=0;j<640;j++)
		{
			tab[i][j][0] = i > 255 ? 255 : (i)%256;
			tab[i][j][1] = i > 255 ? 255 : (i)%256;
			tab[i][j][2] = i > 255 ? 255 : (i)%256;
		}
				
	printToFile("photoTest", tab, 640, 480);*/
	
	int *test = new int[5];
	for(int i=0; i<5; i++)
		cout << test[i] << endl;
		
	cout << "" << endl;
	delete test;
	
	test = new int[8];
	for(int i=0; i<8; i++)
		cout << test[i] << endl;
	
	int **tab = new int*[100];
	*tab = new int[100*100];
	
	for(int i=1; i<100; i++)
	{
		tab[i] = tab[i-1] + 100;
	}
	
	for(int i=0; i<100; i++)
	{
		for(int j=0; j<100; j++)
		{
			cout << tab[i][j] << " ";
		}
		cout << "" << endl;
	}
			
	return 0;
}
