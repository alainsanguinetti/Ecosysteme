# MAKEFILE
# Adam Alouani and Alain Sanguinetti, 2014

CFLAGS=-g -W -Wall
LDFLAGS= -L -lSDL -lSDLmain -lSDL_image -lSDL_ttf

ecosysteme: ecosysteme.o
	gcc -o ecosysteme ecosysteme.o $(LDFLAGS)

ecosysteme.o: ecosysteme.c ./src/struct.h
	gcc -o ecosysteme.o -c ecosysteme.c $(CFLAGS)

clean:
	rm -rf *.o
