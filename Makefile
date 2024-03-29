INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/lib/

COMPILERFLAGS = -Wall 
CC = g++
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm

All: project

project: Boot.o
	$(CC) $(CFLAGS) -lglut -lGLU -lGL City.cpp Boot.cpp Building.cpp Block.cpp Robot.cpp Street.cpp -o Boot
	./Boot
