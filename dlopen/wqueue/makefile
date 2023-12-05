CFLAGS = -g -Wall

wqueue: wqueue.o
	gcc wqueue.o -ldl -o wqueue -rdynamic

wqueue.o: wqueue.c
	gcc -c $(CFLAGS) wqueue.c

clean:
	rm -rf *.o wqueue
