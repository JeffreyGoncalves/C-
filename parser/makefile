CXX=g++
CXXFLAGS=-Wall -ansi -I./ -g
LDFLAGS= -g -lfl

all : parsing

parsing : parsing.o
	$(CXX) -o $@ $^ $(LDFLAGS)
	
%.o : %.c
	$(CXX) -o $@ -c $^ $(CXXFLAGS)
	
#clean : parsing.o
#	rm -rf $^ 
	
