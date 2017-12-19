OBJ=main.o Object3D.o sphere.o Point3D.o vec3D.o ray3D.o color.o Scene.o Camera.o source.o ecran.o
CXX=g++
CXXFLAGS=-Wall -ansi -I./ -g -fopenmp
LDFLAGS= -g -lfl -fopenmp

all : copy test clean

copy :
	cp main/main.cpp Object3D/*.cpp Object3D/*.h Point3D/*.cpp Point3D/*.h vec3D/*.cpp vec3D/*.h ray3D/*.cpp ray3D/*.h sphere/*.cpp sphere/*.h \
			color/*.cpp color/*.h Scene/*.cpp Scene/*.h source/*.cpp source/*.h Camera/*.cpp Camera/*.h ecran/*.cpp ecran/*.h .

test : $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS)
	
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $^
	
clean:
	rm -f *.o *.cpp *.h
