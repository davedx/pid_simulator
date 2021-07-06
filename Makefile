sim: sim.o renderer.o util.o controller.o
	clang -o sim sim.o renderer.o util.o controller.o -framework GLUT -framework OpenGL -framework Cocoa

controller.o: controller.c
	clang -c controller.c

renderer.o: renderer.c
	clang -c renderer.c

util.o: util.c
	clang -c util.c

sim.o: sim.c macros.h renderer.h
	clang -c sim.c
