all: main.o
	gcc -o game main.o `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image

main.o: main.c
	gcc -c main.c

run:
	export SDL_VIDEODRIVER=dummy
	./game

clean:
	rm -rf game
	rm -rf *.o
