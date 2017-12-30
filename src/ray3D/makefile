CXX=g++
CXXFLAGS=-Wall -ansi -I./ -g -fopenmp

all : cpy ray3D.o clean

cpy ::
	@cp -f ../Point3D/*.h ../vec3D/*.h .
	
ray3D.o : ray3D.cpp
	$(CXX) $(CXXFLAGS) -o ../$@ -c $^
	
clean ::
	@rm -rf Point3D.h vec3D.h
