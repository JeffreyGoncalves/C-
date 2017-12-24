CXX=g++
CXXFLAGS=-Wall -ansi -I./ -g -fopenmp

all : cpy sphere.o clean

cpy : 
	@cp -f ../Point3D/*.h ../color/*.h ../Object3D/*.h ../vec3D/*.h ../ray3D/*.h .
	
sphere.o : sphere.cpp
	$(CXX) $(CXXFLAGS) -o ../$@ -c $^
	
clean :
	@rm -rf Point3D.h color.h Object3D.h vec3D.h ray3D.h
