/*
	Programa para simular uma fila de espera

	Objectivo: exemplificar a utilização de uma lista ligada
				e a alocação dinâmica.

	Usando lista não intrusiva duplamente ligada com sentinela
	implementada em separado
*/
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"

/*-----------------------------------------------------------------------------
	Representa um utente na fila de espera
 */
typedef struct User {
	time_t arrival;
	char *name;
} User;

/*-----------------------------------------------------------------------------
	A fila de espera
 */
static List_node *queue;

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
	list_insert_rear(queue, user);
}

/*-----------------------------------------------------------------------------
	Função para remover da fila o primeiro utente a ser atendido
 */
char *user_answer() {
	if (list_empty(queue))
		return NULL;
	List_node *node = list_front(queue);
	User *user = list_data(node);
	list_remove(node);

	char *name = user->name;
	free(user);
	return name;
}

/*-----------------------------------------------------------------------------
	Função para remover um utente da fila de espera, por desistencia
 */
static int cmp(const void *a, const void *b) {
	return strcmp(((User *)a)->name, (char *)b) == 0;
}

static void user_remove(char *name) {
	if (list_empty(queue))
		return;
	List_node *node = list_search(queue, cmp, name);
	if (node == NULL)
		return;
	User *user = list_data(node);
	list_remove(node);
	free(user->name);
	free(user);
}

/*-----------------------------------------------------------------------------
	Listar os utentes na fila de espera.
 */

static void print(void *user) {
	printf("Nome: %s, %ld\n", ((User *)user)->name,
			time(NULL) - ((User *)user)->arrival);
}

void user_print() {
	if (list_empty(queue)) {
		printf("Fila vazia\n");
		return;
	}
	list_foreach(queue, print);
}

/*-----------------------------------------------------------------------------
	Vazar a lista libertando toda a memória alocada.
 */

void free_user(void *user) {
	free(((User *)user)->name);
	free(user);
}

void user_leak_queue() {
	list_foreach(queue, free_user);
	list_destroy(queue);
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
	queue = list_create();
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


