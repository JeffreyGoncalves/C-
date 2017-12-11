#include "source.h"

Source::Source(){

	position = new Point3D();
	lightColor = new Color();
}

Source::Source(Point3D p, Color c){

	position =&p;
	lightColor = new Color(c);
}

Source::Source(double x,double y,double z,int r, int g,int b){

	position = new Point3D(x,y,z);
	lightColor = new Color(r,g,b);
}