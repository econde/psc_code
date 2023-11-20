
CFLAGS = -c -g -Werror -Wall -pedantic -std=c11 -I../include

LFLAGS=

VPATH = ../lib

all: wqueue1 wqueue2 wqueue3 wqueue4 wqueue5 wqueue6

%.o: %.c
	gcc -o $*.o $(CFLAGS) $<

wqueue1: wqueue1.o
	gcc $(LFLAGS) wqueue1.o -o wqueue1

wqueue2: wqueue2.o
	gcc $(LFLAGS) wqueue2.o -o wqueue2

wqueue3: wqueue3.o
	gcc $(LFLAGS) wqueue3.o -o wqueue3

wqueue4: wqueue4.o list.o
	gcc $(LFLAGS) wqueue4.o list.o -o wqueue4

wqueue5: wqueue5.o ilist.o
	gcc $(LFLAGS) wqueue5.o ilist.o -o wqueue5

wqueue6.o: wqueue6.c
	gcc -o $*.o $(CFLAGS) `pkg-config glib-2.0 --cflags` $<

wqueue6: wqueue6.o
	gcc $(LFLAGS) wqueue6.o `pkg-config glib-2.0 --libs` -o wqueue6

clean:
	rm -rf *.o wqueue1 wqueue2 wqueue3 wqueue4 wqueue5 a.out
