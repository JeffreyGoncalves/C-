#include "sphere.h"

int main(){

	return 0;
}
 
Sphere::Sphere(int x, int y, int z, int r, Color C, float ref){

	centerx = x;
	centery = y;
	centerz = z;
	radius = r;
	rgb = C;
	reflexion = ref;
}

Sphere::Sphere(){

	centerx =0;
	centery = 0;
	centerz = 0;
	radius = 0;
	rgb = new Color();
	reflexion = 0.0;
}

void Sphere::setCenter(int x, int y, int z){

	centerx = x;
	centery = y;
	centerz = z;
}

