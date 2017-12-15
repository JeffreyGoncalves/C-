#ifndef SOURCE_H
#define SOURCE_H

#include <iostream>
#include "Point3D.h"
#include "color.h"


class Source
{
	Point3D *position;
	Color *lightColor;
	static const double rayon = 0.5;

public:
	Source();
	Source(Point3D p, Color c);
	Source(double x,double y,double z,int r, int g , int b);
	Source(const Source &s);
	~Source();
	
};

#endif 
