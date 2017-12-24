CXX=g++
CXXFLAGS=-Wall -ansi -I./ -g -fopenmp

all : cpy vec3D.o clean

cpy : 
	@cp -f ../Point3D/*.h .
	
vec3D.o : vec3D.cpp
	$(CXX) $(CXXFLAGS) -o ../$@ -c $^
	
clean :
	@rm -rf Point3D.h
