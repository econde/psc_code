
CFLAGS = -c -g -Werror -Wall -pedantic -I../include

LFLAGS=

VPATH = ../lib

all: wc_vector wc_tree wc_htable

%.o: %.c
	gcc -o $*.o $(CFLAGS) $<

wc_htable.o: wc_htable.c
	gcc $(CFLAGS) wc_htable.c -o wc_htable.o 

wc_tree.o: wc_tree.c
	gcc $(CFLAGS) wc_tree.c -o wc_tree.o 

wc_vector.o: wc_vector.c
	gcc $(CFLAGS) wc_vector.c -o wc_vector.o 

wc_htable: wc_htable.o htable.o list.o
	gcc	$(LFLAGS) wc_htable.o htable.o list.o -o wc_htable
	
wc_tree: wc_tree.o tree.o
	gcc	$(LFLAGS) wc_tree.o tree.o -o wc_tree

wc_vector: wc_vector.o vector.o
	gcc	$(LFLAGS) wc_vector.o vector.o -o wc_vector


clean:
	rm -rf *.o wc_tree wc_vector wc_htable
