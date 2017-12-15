#include "sphere.h"
 
Sphere::Sphere(double x, double y, double z, double r, Color C, double ref) : Object3D(C, ref), center(x,y,z), radius(r) {}

Sphere::Sphere() : Object3D(), center(), radius(0.d) {}

void Sphere::setCenter(double x, double y, double z){

	Point3D new_center(x,y,z);
	center = new_center;
}

void Sphere::setCenter(Point3D new_center)
{
	center = new_center;
}

Point3D* Sphere::detectCollision(ray3D ray)
{
	//Resout l'equation decrivant les points d'impact du rayon ray sur la sphere
	//de la forme a*t² + b*t + c = 0
	double x_dir = ray.getRayDirection().getXCoor(),
		   y_dir = ray.getRayDirection().getYCoor(),
		   z_dir = ray.getRayDirection().getZCoor(),
		   //Direction du rayon
		   
		   x_rayO = ray.getOrigin().getXCoor(),
		   y_rayO = ray.getOrigin().getXCoor(),
		   z_rayO = ray.getOrigin().getXCoor(),
		   //Point d'origine du rayon
		   
		   x_center = center.getXCoor(),
		   y_center = center.getYCoor(),
		   z_center = center.getZCoor();
		   //Centre de la sphere
	
	//Definition de a,b et c  
	double a = pow(x_dir, 2) + pow(y_dir, 2) + pow(z_dir, 2),
		   b = 2*(x_dir*(x_rayO - x_center) + y_dir*(y_rayO - y_center) + z_dir*(z_rayO - z_center)),
		   c = pow(x_rayO-x_center, 2) + pow(y_rayO-y_center, 2) + pow(z_rayO-z_center, 2) - radius;
		   
	//Calcul du determinant
	double delta = b*b - 4*a*c;
	double r_1 = 0, r_2 = 0, r_toReturn = 0;	//racines du polynome
	
	//delta < 0 -> t est complexe donc non valide
	if(delta < 0)return NULL;	
	
	//delta = 0 -> une racine
	else if(delta == 0)
	{
		r_1 = -b/(2*a);
		if(r_1 < 0) return NULL;
		else r_toReturn = r_1;
	}
	
	//delta > 0 -> deux racines reeles
	else 						
	{
		r_1 = (-b-sqrt(delta))/(2*a);
		r_2 = (-b+sqrt(delta))/(2*a);
		if(r_1 >= 0)
		{
			if(r_2 >= 0)
			{
				if(r_1 < r_2) r_toReturn = r_1;
				else 		  r_toReturn = r_2;
			}
			else r_toReturn = r_1;
		}
		else if(r_2 >= 0) r_toReturn = r_2;
		else return NULL;
	}		
	
	
	return new Point3D(x_rayO + r_toReturn*x_dir, 
					   y_rayO + r_toReturn*y_dir, 
					   z_rayO + r_toReturn*z_dir);				
}

vec3D Sphere::calcNormToPoint(Point3D p)
{
	vec3D v(this->center, p);
	return v.normalize();
}

//Surcharge de << 
std::ostream& operator<< (std::ostream &os, const Sphere &s)
{
	return os << "center=" << s.center << ", radius=" << s.radius;
}
