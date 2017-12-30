CXX=g++
CXXFLAGS=-Wall -ansi -I./ -g -fopenmp

all : cpy Object3D.o clean

cpy ::
	@cp -f ../Point3D/*.h ../ray3D/*.h ../vec3D/*.h ../color/*.h .
	
Object3D.o : Object3D.cpp
	$(CXX) $(CXXFLAGS) -o ../$@ -c $^
	
clean ::
	@rm -rf Point3D.h ray3D.h vec3D.h color.h
