
CFLAGS = -c -g -Werror -Wall -pedantic -I../include

LFLAGS=

VPATH = ../lib

all: cword_vector cword_tree cword_htable cword_list

%.o: %.c
	gcc -o $*.o $(CFLAGS) $<

cword_htable.o: cword_htable.c
	gcc $(CFLAGS) cword_htable.c -o cword_htable.o

cword_tree.o: cword_tree.c
	gcc $(CFLAGS) cword_tree.c -o cword_tree.o

cword_vector.o: cword_vector.c
	gcc $(CFLAGS) cword_vector.c -o cword_vector.o

cword_htable: cword_htable.o htable.o slist.o
	gcc	$(LFLAGS) cword_htable.o htable.o slist.o -o cword_htable

cword_tree: cword_tree.o tree.o
	gcc	$(LFLAGS) cword_tree.o tree.o -o cword_tree

cword_vector: cword_vector.o vector.o
	gcc	$(LFLAGS) cword_vector.o vector.o -o cword_vector

cword_list: cword_list.o list.o
	gcc	$(LFLAGS) cword_list.o list.o -o cword_list

clean:
	rm -rf *.o cword_tree cword_vector cword_htable
