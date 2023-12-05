/*
	Programa para simular uma fila de espera

	Objectivo: exemplificar a utilização de uma lista ligada
			e a alocação dinâmica.

	Criando diretamente uma lista intrusiva duplamente ligada com sentinela
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

/*-----------------------------------------------------------------------------
	A fila de espera é representada por um elemento User,
	utilizado como sentinela
 */

#include "user.h"

User queue = {.next = &queue, .prev = &queue, .name = NULL};

/*-----------------------------------------------------------------------------
	Função para insertir um novo utente na fila de espera
 */
static void user_insert(char *name) {
	User *user = malloc(sizeof *user);
	if (NULL == user) { \
		fprintf(stderr, "Out of memory");
		exit(-1);
	}
	user->name = strdup(name);
	if (NULL == user->name) { \
		fprintf(stderr, "Out of memory");
		exit(-1);
	}

	user->next = queue.next;
	user->prev = &queue;
	queue.next->prev = user;
	queue.next = user;
}

/*-----------------------------------------------------------------------------
	Função para remover da fila o primeiro utente a ser atendido
 */
static void user_answer(char *unused) {
	if (queue.next == &queue)
		printf("Fila vazia\n");
	User * p = queue.prev;
	p->prev->next = p->next;
	p->next->prev = p->prev;

	printf("Atender %s\n", p->name);
	free(p->name);
	free(p);
}

/*-----------------------------------------------------------------------------
	Função para remover um utente da fila de espera por desistência
 */
static void user_remove(char *name) {
	if (queue.next == &queue)
		return;
	User *p;
	for (p = queue.next; p != &queue; p = p->next)
		if (strcmp(name, p->name) == 0)
			break;
	if (p != &queue) {
		p->prev->next = p->next;
		p->next->prev = p->prev;
		char *aux = p->name;
		free(p);
		free(aux);
	}
}

/*-----------------------------------------------------------------------------
	Listar os utentes na fila de espera.
 */
static void user_print() {
	if (queue.next == &queue) {
		printf("Fila vazia\n");
		return;
	}
	User * p;
	int i;
	for (i = 1, p = queue.prev; p != &queue; p = p->prev, ++i)
		printf("%d: %s\n", i, p->name);
}

/*=====================================================================
 * Commands
 */

typedef struct command {
	void (*f) (char *);
	char c;
	char *desc;
	struct command *next;
} Command;

static Command *commands = NULL;

void command_insert(char c, char *desc, void (*f)(char *)) {
	Command *new_command = malloc(sizeof (Command));
	new_command->c = c;
	new_command->desc = strdup(desc);
	new_command->f = f;
	new_command->next = commands;
	commands = new_command;
}

void command_execute(char c, char *param) {
	for (Command *p = commands; p != NULL; p = p->next)
		if (p->c == c) {
			p->f(param);
			return;
		}
}

void command_list(char *unused) {
	for (Command *p = commands; p != NULL; p = p->next)
		printf("%c%s\n", p->c, p->desc);
}

#include <dlfcn.h>

static void *handle;

static void command_new(char *lib) {
	handle = dlopen(lib, RTLD_LAZY);
	if (handle == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return;
	}
	void (*f)(char *) = dlsym(handle, "command_function");
	if (f == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return;
	}
	char *c = dlsym(handle, "command_letter");
	if (c == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return;
	}
	char **desc = dlsym(handle, "command_description");
	if (desc == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		return;
	}
	command_insert(*c, *desc, f);
}

void leave_program(char *unused) {
	void *next;
	for (User *p = queue.next; p != &queue; p = next) {
		next = p->next;
		p->prev->next = p->next;
		p->next->prev = p->prev;
		free(p->name);
		free(p);
	}
	for (Command *p = commands; p != NULL; p = next) {
		next = p->next;
		free(p->desc);
		free(p);
	}
	if (handle != NULL)
		dlclose(handle);
	exit(0);
}

int main() {
	char line[100];
	command_insert('s', "\t - Sair", leave_program);
	command_insert('h', "\t - Listar comandos existentes", command_list);
	command_insert('c', "\t - Incorporar novo comando", command_new);
	command_insert('d', " <nome> - Desistencia de utente", user_remove);
	command_insert('l', "\t - Listar fila de espera", user_print);
	command_insert('a', "\t - Atender utente", user_answer);
	command_insert('n', " <nome> - Chegada de novo utente", user_insert);

	while (1) {
		putchar('>');
		fgets(line, sizeof line, stdin);
		char *command = strtok(line, " \n");
		char *name = strtok(NULL, " \n");
		if (command != NULL)
			command_execute(*command, name);
	}
}


