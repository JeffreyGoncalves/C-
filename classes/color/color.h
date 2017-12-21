#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <cstdio>
#include <ctime> 
#include <cstdlib>

class Color
{
	int red, blue,green;
public:
	Color();
	Color(int r, int g, int b);
	void setColor(int r, int g, int b);
	int const& getRed();
	int const& getGreen();
	int const& getBlue();
	
	Color times(double t);
	
	//Operateurs +=, -=, + , -, *= et *
	Color operator+= (Color const& c);
	Color operator-= (Color const& c);
	Color operator+ (Color const& c);
	Color operator- (Color const& c);
	Color operator*= (Color const& c);
	Color operator* (Color const& c);
	friend std::ostream& operator<< (std::ostream &os, Color const& c);
};

#endif
