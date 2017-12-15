OBJ=main.o Object3D.o sphere.o Point3D.o vec3D.o ray3D.o color.o
CXX=g++
CXXFLAGS=-Wall -ansi -I./ -g
LDFLAGS= -g -lfl

all : copy test clean

copy :
	cp main/main.cpp Object3D/*.cpp Object3D/*.h Point3D/*.cpp Point3D/*.h vec3D/*.cpp vec3D/*.h ray3D/*.cpp ray3D/*.h sphere/*.cpp sphere/*.h color/*.cpp color/*.h .

test : $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $^

Object3D.o : Object3D.cpp 
	$(CXX) $(CXXFLAGS) -c $^
	
sphere.o : sphere.cpp 
	$(CXX) $(CXXFLAGS) -c $^
	
Point3D.o : Point3D.cpp
	$(CXX) $(CXXFLAGS) -c $^
	
vec3D.o : vec3D.cpp 
	$(CXX) $(CXXFLAGS) -c $^
	
ray3D.o : ray3D.cpp
	$(CXX) $(CXXFLAGS) -c $^
	
color.o : color.cpp
	$(CXX) $(CXXFLAGS) -c $^

clean:
	rm -f *.o *.cpp *.h
