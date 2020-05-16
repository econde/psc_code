
CFLAGS = -c -g -Werror -Wall -std=c11  -pedantic -I../include

LFLAGS=

VPATH = ../lib

all: wqueue1 wqueue2 wqueue3 wqueue4 wqueue5

%.o: %.c
	gcc -o $*.o $(CFLAGS) $<

wqueue1: wqueue1.o
	gcc $(LFLAGS) wqueue1.o -o wqueue1

wqueue2: wqueue2.o
	gcc $(LFLAGS) wqueue2.o -o wqueue2

wqueue3: wqueue3.o
	gcc $(LFLAGS) wqueue3.o -o wqueue3

wqueue4: wqueue4.o listd.o
	gcc $(LFLAGS) wqueue4.o listd.o -o wqueue4
	
wqueue5: wqueue5.o listdi.o
	gcc $(LFLAGS) wqueue5.o listdi.o -o wqueue5

clean:
	rm -rf *.o wqueue1 wqueue2 wqueue3 wqueue4 wqueue5
