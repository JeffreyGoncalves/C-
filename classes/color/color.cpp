#include "color.h"

Color::Color(int r, int g, int b){

	red = r;
	green = g;
	blue = b;
	if(!((r>=0 && r<256) && (g>=0 && g<256) && (b>=0 && b<256))){
		
		std::cout << "Valeurs incorrectes !!\nr = " << r << "g = " << g << "b =" << b <<"\n";
		//On redefinit alors la couleur correctement
		//Rouge
		if(r>255)red = 255;
		else if(r<0)red = 0;
		//Vert
		if(g>255)green = 255;
		else if(g<0)green = 0;
		//Bleu
		if(b>255)blue = 255;
		else if(b<0)blue = 0;
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

int const& Color::getRed(){ return red; }
int const& Color::getGreen(){ return green; }
int const& Color::getBlue(){ return blue; }

Color Color::times(double t)
{
	int newRed = int(double(this->red) * t),
	    newBlue = int(double(this->green) * t),
	    newGreen = int(double(this->blue) * t);
	 
	if(newRed > 255)newRed = 255;
	if(newBlue > 255)newBlue = 255;
	if(newGreen > 255)newRed = 255;
	    
	return Color(newRed, newBlue, newGreen); 
}

//Operateurs +=, -=, +, , *=, et *
Color Color::operator+= (Color const& c)
{
	this->red += c.red;
	if(this->red > 255) this->red = 255;
	
	this->blue += c.blue;
	if(this->blue > 255) this->blue = 255;
	
	this->green += c.green;
	if(this->green > 255) this->green = 255;
	
	return *this;
}

Color Color::operator-= (Color const& c)
{
	this->red -= c.red;
	if(this->red < 0) this->red = 0;
	
	this->blue -= c.blue;
	if(this->blue < 0) this->blue = 0;
	
	this->green -= c.green;
	if(this->green < 0) this->green = 0;
	
	return *this;
}

Color Color::operator+ (Color const& c)
{
	Color toReturn(0,0,0);
	toReturn += *this;
	toReturn += c;
	return toReturn;
}

Color Color::operator- (Color const& c)
{
	Color toReturn(0,0,0);
	toReturn += *this;
	toReturn -= c;
	return toReturn;
}

Color Color::operator*= (Color const& c)
{
	this->red *= c.red;
	if(this->red > 255) this->red = 255;
	
	this->blue *= c.blue;
	if(this->blue > 255) this->blue = 255;
	
	this->green *= c.green;
	if(this->green > 255) this->green = 255;
	
	return *this;
}

Color Color::operator* (Color const& c)
{
	Color toReturn(0,0,0);
	toReturn += *this;
	toReturn *= c;
	return toReturn;
}

