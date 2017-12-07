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
	int getRed();
	int getGreen();
	int getBlue();
};

#endif
