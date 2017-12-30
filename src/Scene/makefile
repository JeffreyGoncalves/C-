CXX=g++
CXXFLAGS=-Wall -ansi -I./ -g -fopenmp

all : cpy Scene.o clean

cpy :: 
	@cp -f ../Object3D/*.h ../sphere/*.h ../triangle/*.h ../tPyramid/*.h ../color/*.h ../source/*.h ../Camera/*.h \
		   ../ecran/*.h ../Point3D/*.h ../ray3D/*.h ../vec3D/*.h .
	
Scene.o : Scene.cpp
	$(CXX) $(CXXFLAGS) -o ../$@ -c $^
	
clean ::
	@rm -rf Object3D.h sphere.h triangle.h tPyramid.h color.h source.h Camera.h ecran.h Point3D.h ray3D.h vec3D.h
