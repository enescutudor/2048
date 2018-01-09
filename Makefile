build:2048.c
	gcc -Wall 2048.c -o 2048 -lncurses
clean:
	rm 2048
run:
	./2048
