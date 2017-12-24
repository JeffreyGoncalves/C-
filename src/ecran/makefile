CXX=g++
CXXFLAGS=-Wall -ansi -I./ -g -fopenmp

all : cpy ecran.o clean

cpy : 
	@cp -f ../Point3D/*.h ../vec3D/*.h .
	
ecran.o : ecran.cpp
	$(CXX) $(CXXFLAGS) -o ../$@ -c $^
	
clean :
	@rm -rf Point3D.h vec3D.h
