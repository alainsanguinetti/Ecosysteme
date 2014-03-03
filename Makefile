# MAKEFILE
# Adam Alouani and Alain Sanguinetti, 2014

CFLAGS=-g -W -Wall
LDFLAGS= -L -lSDL -lSDLmain -lSDL_image -lSDL_ttf 

ecosysteme: ecosysteme.o ./src/struct.o ./disp/disp.o ./src/days.o
	gcc -o ecosysteme ecosysteme.o ./src/struct.o ./disp/disp.o ./src/days.o $(LDFLAGS)

ecosysteme.o: ecosysteme.c ./src/struct.h
	gcc -o ecosysteme.o -c ecosysteme.c $(CFLAGS)
	
./src/struct.o: ./src/struct.h ./src/struct.c
	gcc -o ./src/struct.o -c ./src/struct.c $(CFLAGS)
	
./disp/disp.o: ./disp/disp.h ./disp/disp.c
	gcc -o ./disp/disp.o -c ./disp/disp.c $(CFLAGS)

./src/days.o: ./src/days.h ./src/days.c
	gcc -o ./src/days.o -c ./src/days.c $(CFLAGS)

clean:
	rm -rf *.o
