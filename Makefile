sim: sim.o cube.o util.o
	clang -o sim sim.o cube.o util.o -framework GLUT -framework OpenGL -framework Cocoa

cube.o: cube.c
	clang -c cube.c

util.o: util.c
	clang -c util.c

sim.o: sim.c macros.h cube.h
	clang -c sim.c
