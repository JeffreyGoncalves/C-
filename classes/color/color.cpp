#include "color.h"

Color::Color(int r, int g, int b){

	if((r>=0 && r<256) && (g>=0 && g<256) && (b>=0 && b<256)){

		red = r;
		green = g;
		blue = b;
	}
	else{

		std::cout << "Valeurs incorrectes !!\nr = " << r << "g = " << g << "b =" << b <<"\n";
	}
}

Color::Color(){

	srand(time(NULL));
	red = rand()%256;
	green = rand()%256;
	blue = rand()%256;
}

void Color::setColor(int r, int g, int b){

	if((r>0 && r<256) && (g>0 && g<256) && (b>0 && b<256)){

		red = r;
		green = g;
		blue = b;
	}
	else{

		std::cout << "Valeurs incorrectes !!\nr = " << r << "g = " << g << "b =" << b <<"\n";
	}
}

int Color::getRed(){ return red; }
int Color::getGreen(){ return green; }
int Color::getBlue(){ return blue; }
