CXX=g++
CXXFLAGS=-Wall -ansi -I./ -g -fopenmp

all : cpy source.o clean

cpy : 
	@cp -f ../Point3D/*.h ../color/*.h ../ray3D/*.h ../vec3D/*.h .
	
source.o : source.cpp
	$(CXX) $(CXXFLAGS) -o ../$@ -c $^
	
clean :
	@rm -rf Point3D.h color.h ray3D.h vec3D.h
