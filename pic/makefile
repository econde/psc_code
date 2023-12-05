CFLAGS = -c -Wall -std=c2x -g --save-temps -Og

all: libexa.so main

main.o: main.c
	gcc $(CFLAGS) main.c -o main.o

libexa.o: libexa.c
	gcc $(CFLAGS) -fPIC libexa.c -o libexa.o

libexa.so: libexa.o
	gcc -shared -o libexa.so libexa.o

main: main.o
	gcc main.o -L. -lexa -o main

clean:
	rm -rf *.o *.i main
