/*
	Programa para simular uma fila de espera

	Objectivo: exemplificar a utilização de uma lista ligada
				e a alocação dinâmica.

	Criando diretamente uma lista intrusiva duplamente ligada com sentinela
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*-----------------------------------------------------------------------------
	Representa um utente na fila de espera
 */
typedef struct User {
	struct User *next, *prev;
	char *name;
} User;

/*-----------------------------------------------------------------------------
	A fila de espera é representada por elemento User, usado como sentinela
 */
static User queue = { .next = &queue, .prev = &queue};

/*-----------------------------------------------------------------------------
	Função para insertir um novo utente na fila de espera
 */
static void user_insert(char *name) {
	User * user = malloc(sizeof *user);
	if (NULL == user) {
		fprintf(stderr, "Out of memory\n");
		exit(-1);
	}
	user->name = malloc(strlen(name) + 1);
	if (NULL == user->name) {
		free(user);
		fprintf(stderr, "Out of memory\n");
		exit(-1);
	}
	strcpy(user->name, name);

	user->prev = queue.prev;
	user->next = &queue;
	queue.prev->next = user;
	queue.prev = user;
}

/*-----------------------------------------------------------------------------
	Função para remover da fila o primeiro utente a ser atendido
 */
char *user_answer() {
	if (queue.next == &queue)
		return NULL;
	User *user = queue.next;
	user->next->prev = user->prev;
	user->prev->next = user->next;
	
	char *name = user->name;
	free(user);
	return name;
}

/*-----------------------------------------------------------------------------
	Função para remover um utente da fila de espera por desistência
 */
static void user_remove(char * name) {
	if (queue.next == &queue)
		return;
	for (User *user = queue.next; user != &queue; user = user->next)
		if (strcmp(name, user->name) == 0) {
			user->prev->next = user->next;
			user->next->prev = user->prev;
			free(user->name);
			free(user);
			return;
		}
}

/*-----------------------------------------------------------------------------
	Listar os utentes na fila de espera.
 */
void user_print() {
	if (queue.next == &queue) {
		printf("Fila vazia\n");
		return;
	}
	int i = 1;
	for (User *user = queue.next; user != &queue; user = user->next)
		printf("%d: %s\n", i++, user->name);
}

/*-----------------------------------------------------------------------------
	Vazar a lista libertando toda a memória alocada.
 */
void user_leak_queue() {
	for (User *next, *p = queue.next; p != &queue; p = next) {
		next = p->next;
		free(p->name);
		free(p);
	}
}

static void help() {
	printf("Comandos:\n"
		"\tS\t\t- Sair\n"
		"\tN <name> \t- Chegada de novo utente\n"
		"\tD <name>\t- Desistencia de utente\n"
		"\tL\t\t- Listar fila de espera\n"
		"\tA\t\t- Atender utente\n");
}

int main() {
	char line[100];
	while (1) {
		if (fgets(line, sizeof(line), stdin) == NULL)
			exit(1);
		char * command = strtok(line, " \n");
		char * name = strtok(NULL, " \n");
		switch (command[0]) {
			case 's':
			case 'S':
				user_leak_queue();
				exit(0);
			case 'h':
			case 'H':
				help();
				break;
			case 'n':
			case 'N':
				user_insert(name);
				break;
			case 'd':
			case 'D':
				user_remove(name);
				break;
			case 'l':
			case 'L':
				user_print();
				break;
			case 'a':
			case 'A':
				name = user_answer();
				if (NULL == name)
					printf("Fila vazia\n");
				else {
					printf("Atender %s\n", name);
					free(name);
				}
				break;
		}
	}
}


