#include <stdlib.h>
#include "user.h"

extern User queue;

void command_function(char *name) {
	User *next;
	for (User *p = queue.next; p != &queue; p = next) {
		next = p->next;
		free(p->name);
		free(p);
	}
	queue.next = queue.prev = &queue;
}

char command_letter = 'k';

char *command_description = "\t - Eliminar todos os utentes da fila de espera";
