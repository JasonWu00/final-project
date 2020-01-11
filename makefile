all: main.o
	gcc -o game main.o `sdl2-config --cflags --libs` -l SDL2 -l SDL2_image

main.o: main.c
	gcc -c main.c

run:
	./game

clean:
	rm -rf game
	rm -rf *.o
