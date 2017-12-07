#include <iostream>
#include <cstdio>
//#include <SDL2/SDL.h>

#include "color.h"
#include "Object3D.h"
#include "sphere.h"

int main(int arc, char** argv)
{
	Object3D *S = new Sphere(0,0,0,10, Color(100, 100, 100), 1.f);
	return 0;
}
