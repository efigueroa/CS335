CC     = g++
CFLAGS = -I../include -pthread -O1

LIB    = ../lib/x11/libglfw.a 
LFLAGS = $(LIB) -lrt -lX11 -lGLU -lGL -pthread -lm -lXrandr 

all: game 

game: main.o functions.o cfonts.o fonttex.o 
	g++ $(CFLAGS) main.o functions.o cfonts.o fonttex.o $(LFLAGS) -o game 

main.o: main.cpp functions.cpp 
	g++ -c $(CFLAGS) main.cpp

functions.o: functions.cpp
	g++ $(CFLAGS) -c functions.cpp
	
cfonts.o: cfonts.c
	gcc $(CFLAGS) -c cfonts.c

fonttex.o: fonttex.c
	gcc $(CFLAGS) -c fonttex.c



clean:
	rm -f game
	rm -f *.o

