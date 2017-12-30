CXX=g++
CXXFLAGS=-Wall -ansi -I./ -g -fopenmp

all : cpy Camera.o clean

cpy :: 
	@cp -f ../Point3D/*.h .

Camera.o : Camera.cpp
	$(CXX) $(CXXFLAGS) -o ../$@ -c $^
	
clean :: 
	@rm -rf Point3D.h
