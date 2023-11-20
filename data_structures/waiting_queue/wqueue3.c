/*
	Programa para simular uma fila de espera

	Objectivo: exemplificar a utilização de uma lista
				não intrusiva duplamente ligada
				e a alocação dinâmica.
*/
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*-----------------------------------------------------------------------------
	Nó para formar lista não intrusiva
 */
typedef struct List_Node {
	struct List_Node *next, *prev;
	void *data;
} List_node;

/*-----------------------------------------------------------------------------
	Representa um utente na fila de espera
 */
typedef struct User {
	time_t arrival;
	char *name;
} User;

/*-----------------------------------------------------------------------------
	A fila de espera é representada por estes dois ponteiros
 */
static List_node queue = { .next = &queue, .prev = &queue};

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
	time(&user->arrival);

	List_node *node = malloc(sizeof *node);
	if (NULL == user->name) {
		free(user->name);
		free(user);
		fprintf(stderr, "Out of memory\n");
		exit(-1);
	}

	node->data = user;

	node->next = &queue;
	node->prev = queue.prev;
	queue.prev->next = node;
	queue.prev = node;
}

/*-----------------------------------------------------------------------------
	Função para remover da fila o primeiro utente a ser atendido
 */
char *user_answer() {
	if (&queue == queue.next)
		return NULL;
	User *user = queue.next->data;

	List_node *node = queue.next;
	node->next->prev = node->prev;
	node->prev->next = node->next;
	free(node);

	char *name = user->name;
	free(user);
	return name;
}

/*-----------------------------------------------------------------------------
	Função para remover um utente da fila de espera, por desistencia
 */
static void user_remove(char *name) {
	if (&queue == queue.next)
		return;
	for (List_node *node = queue.next; node != &queue; node = node->next)
		if (strcmp(((User *)node->data)->name, name) == 0) {
			node->next->prev = node->prev;
			node->prev->next = node->next;
			free(((User *)node->data)->name);
			free(node->data);
			free(node);
			return;
		}
}

/*-----------------------------------------------------------------------------
	Listar os utentes na fila de espera.
 */
void user_print() {
	if (&queue == queue.next) {
		printf("Fila vazia\n");
		return;
	}
	for (List_node *node = queue.next; node != &queue; node = node->next)
		printf("Nome: %s, %ld\n", ((User *)node->data)->name,
				time(NULL) - ((User *)node->data)->arrival);
}

/*-----------------------------------------------------------------------------
	Vazar a lista libertando toda a memória alocada.
 */
void user_leak_queue() {
	for (List_node *next, *node = queue.next; node != &queue; node = next) {
		next = node->next;
		free(((User *)node->data)->name);
		free(node->data);
		free(node);
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
	queue.next = queue.prev = &queue;
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


