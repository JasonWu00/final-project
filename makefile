all: main.o
	gcc -o game main.o `sdl2-config --cflags --libs`

main.o: main.c
	gcc -c main.c

run:
	./game

clean:
	rm -rf game
	rm -rf *.o
