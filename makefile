all: main.o testing.o testing.h
	gcc -o game main.o testing.o `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lm

main.o: main.c testing.h
	gcc -c main.c

testing.o: testing.c testing.h
	gcc -c testing.c

run:
	./game

clean:
	rm -rf game
	rm -rf *.o
