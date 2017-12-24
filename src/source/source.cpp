#include "source.h"

Source::Source() : position(), lightColor() {}

Source::Source(Point3D p, Color c) : lightColor(c){
	position = p;
}

Source::Source(double x,double y,double z,int r, int g,int b) : position(x,y,z), lightColor(r,g,b) {}

Source::Source(const Source &s)
{
	this->position = s.position;
	this->lightColor = s.lightColor;
}

Source::~Source(){}

Color const& Source::getSourceColor()
{
	return this->lightColor;
}

Point3D const& Source::getSourceLocation()
{
	return this->position;
}
