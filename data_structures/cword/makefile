
CFLAGS = -c -g -Werror -Wall -pedantic -I../include

LFLAGS=

VPATH = ../lib

all: cword_array cword_vector_ptr cword_vector cword_tree cword_htable cword_list

%.o: %.c
	gcc -o $*.o $(CFLAGS) $<

cword_htable: cword_htable.o htable.o slist.o wordread.o
	gcc	$(LFLAGS) cword_htable.o htable.o slist.o wordread.o -o cword_htable

cword_tree: cword_tree.o tree.o wordread.o
	gcc	$(LFLAGS) cword_tree.o tree.o wordread.o -o cword_tree

cword_vector: cword_vector.o vector.o wordread.o
	gcc	$(LFLAGS) cword_vector.o vector.o wordread.o -o cword_vector

cword_vector_ptr: cword_vector_ptr.o vector_ptr.o wordread.o
	gcc	$(LFLAGS) cword_vector_ptr.o vector_ptr.o wordread.o -o cword_vector_ptr

cword_list: cword_list.o list.o wordread.o
	gcc	$(LFLAGS) cword_list.o list.o wordread.o -o cword_list

cword_array: cword_array.o wordread.o
	gcc	$(LFLAGS) cword_array.o wordread.o -o cword_array

clean:
	rm -rf *.o cword_array cword_list cword_tree cword_vector cword_vector_ptr cword_htable
