all : compile

compile : 
	rm -rf prog
	cd src && $(MAKE) MAKEFLAGS= && mv prog ..

