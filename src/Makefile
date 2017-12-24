OBJ=main.o Object3D.o sphere.o Point3D.o vec3D.o ray3D.o color.o Scene.o Camera.o source.o ecran.o Controller.o
CXX=g++
LDFLAGS= -g -lfl -fopenmp

all : sub_make prog clean

sub_make :
	@cd Camera && $(MAKE) MAKEFLAGS=
	@cd color && $(MAKE) MAKEFLAGS=
	@cd Controller && $(MAKE) MAKEFLAGS=
	@cd ecran && $(MAKE) MAKEFLAGS=
	@cd main && $(MAKE) MAKEFLAGS=
	@cd Object3D && $(MAKE) MAKEFLAGS=
	@cd Point3D && $(MAKE) MAKEFLAGS=
	@cd ray3D && $(MAKE) MAKEFLAGS=
	@cd Scene && $(MAKE) MAKEFLAGS=
	@cd source && $(MAKE) MAKEFLAGS=
	@cd sphere && $(MAKE) MAKEFLAGS=
	@cd vec3D && $(MAKE) MAKEFLAGS=

prog : 
	$(CXX) -o $@ $(OBJ) $(LDFLAGS)
	
clean:
	rm -f *.o
