CXX=g++
CXXFLAGS=-Wall -ansi -I./ -g -fopenmp

all : cpy triangle.o clean

cpy ::
	@cp -f ../Point3D/*.h ../Object3D/*.h ../ray3D/*.h ../vec3D/*.h ../color/*.h .
	
triangle.o : triangle.cpp
	$(CXX) $(CXXFLAGS) -o ../$@ -c $^
	
clean ::
	@rm -rf Point3D.h Object3D.h ray3D.h vec3D.h color.h
