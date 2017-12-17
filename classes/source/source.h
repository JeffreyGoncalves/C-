#ifndef SOURCE_H
#define SOURCE_H

#include <iostream>
#include "Point3D.h"
#include "color.h"
#include "ray3D.h"


class Source
{
	Point3D position;
	Color lightColor;

public:
	Source();
	Source(Point3D p, Color c);
	Source(double x,double y,double z,int r, int g , int b);
	Source(const Source &s);
	~Source();
	
	//Getters
	Color const& getSourceColor();
	Point3D const& getSourceLocation();
};

#endif 
