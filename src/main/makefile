CXX=g++
CXXFLAGS=-Wall -ansi -I./ -g -fopenmp

all : cpy main.o clean

cpy : 
	@cp -f ../Scene/*.h ../Controller/*.h ../ecran/*.h ../color/*.h \
	   ../Object3D/*.h ../sphere/*.h ../ray3D/*.h ../Point3D/*.h \
	   ../vec3D/*.h ../source/*.h ../Camera/*.h .
	
main.o : main.cpp
	$(CXX) $(CXXFLAGS) -o ../$@ -c $^
	
clean :
	@rm -rf Scene.h Controller.h ecran.h color.h Object3D.h \
		   sphere.h ray3D.h Point3D.h vec3D.h source.h Camera.h
		
