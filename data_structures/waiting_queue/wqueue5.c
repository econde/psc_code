/*
	Programa para simular uma fila de espera

	Objectivo: exemplificar a utilização de uma lista ligada
				e a alocação dinâmica.

	Usando lista intrusiva duplamente ligada com sentinela
	implementada em separado
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#include "ilist.h"

/*-----------------------------------------------------------------------------
	Representa um utente na fila de espera
 */
typedef struct User {
	Ilist_node node;
	char *name;
	time_t arrival;
} User;

/*-----------------------------------------------------------------------------
	A fila de espera
 */
static Ilist_node *queue;

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
	}	strcpy(user->name, name);
	time(&user->arrival);
	ilist_insert_rear(queue, &user->node);
}

/*-----------------------------------------------------------------------------
	Função para remover da fila o primeiro utente a ser atendido
 */
char *user_answer() {
	if (ilist_empty(queue))
		return NULL;
	Ilist_node *node = ilist_remove_front(queue);
	User *user = (User*)((char*)node - offsetof(User, node));

	char *name = user->name;
	free(user);
	return name;
}

/*-----------------------------------------------------------------------------
	Função para remover um utente da fila de espera, por desistencia
 */
static int cmp(Ilist_node *node, const void *name) {
	User *user = (User*)((char*)node - offsetof(User, node));
	return strcmp(user->name, name);
}

static void user_remove(char *name) {
	if (ilist_empty(queue))
		return;
	Ilist_node * node = ilist_search(queue, name, cmp);
	if (node == NULL)
		return;
	User *user = (User*)((char*)node - offsetof(User, node));
	ilist_remove(node);
	free(user->name);
	free(user);
}

/*-----------------------------------------------------------------------------
	Listar os utentes na fila de espera.
 */

static void print(Ilist_node *node) {
	User *user = (User*)((char*)node - offsetof(User, node));
	printf("%s, %ld\n", user->name, time(NULL) - user->arrival);
}

void user_print() {
	if (ilist_empty(queue)) {
		printf("Fila vazia\n");
		return;
	}
	ilist_foreach(queue, print);
}

/*-----------------------------------------------------------------------------
	Vazar a lista libertando toda a memória alocada.
 */

void free_user(Ilist_node *node) {
	User *user = (User*)((char*)node - offsetof(User, node));
	free(user->name);
	free(user);
}

void user_remove_queue() {
	ilist_foreach(queue, free_user);
	ilist_destroy(queue);
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
	queue = ilist_create();
	while (1) {
		if (fgets(line, sizeof(line), stdin) == NULL)
			exit(1);
		char * command = strtok(line, " \n");
		char * name = strtok(NULL, " \n");
		switch (command[0]) {
			case 's':
			case 'S':
				user_remove_queue();
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
