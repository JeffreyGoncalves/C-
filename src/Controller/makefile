CXX=g++
CXXFLAGS=-Wall -ansi -I./ -g -fopenmp

all : cpy Controller.o clean

cpy : 
	@cp -f ../Scene/*.h ../Object3D/*.h ../Point3D/*.h ../ray3D/*.h ../vec3D/*.h ../color/*.h \
	   ../sphere/*.h ../source/*.h ../Camera/*.h ../ecran/*.h .
	
Controller.o : Controller.cpp
	$(CXX) $(CXXFLAGS) -o ../$@ -c $^
	
clean :
	@rm -rf Scene.h Object3D.h Point3D.h ray3D.h vec3D.h color.h sphere.h source.h Camera.h ecran.h
