#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>

class Point3D
{
	public :
		//Constructeurs
		///////////////
		Point3D();
		Point3D(double x_coor, double y_coor, double z_coor);
		//Getters
		///////////////
		double const& getXCoor() const;
		double const& getYCoor() const;
		double const& getZCoor() const;
		///////////////
		//Surcharge des operateurs <<
		friend std::ostream& operator<< (std::ostream &os, const Point3D &p);
		
		
	private :
		double x,y,z;
};

#endif
