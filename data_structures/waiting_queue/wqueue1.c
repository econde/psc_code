/*
	Programa para simular uma fila de espera

	Objectivo: exemplificar a utilização de uma lista ligada
				e a alocação dinâmica.

	Criando diretamente uma lista simplesmente ligada
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*-----------------------------------------------------------------------------
	Representa um utente na fila de espera
 */
typedef struct User {
	struct User *next;
	time_t arrival;
	char *name;
} User;

/*-----------------------------------------------------------------------------
	A fila de espera é representada por estes dois ponteiros
 */
static User *head = NULL, *tail = NULL;

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
	user->next = NULL;
	if (NULL == head)
		head = tail = user;
	else {
		tail->next = user;
		tail = user;
	}
}

/*-----------------------------------------------------------------------------
	Função para remover da fila o primeiro utente a ser atendido
 */
char *user_answer() {
	if (NULL == head)
		return NULL;
	User *user = head;
	head = head->next;
	tail = NULL == head ? NULL : tail;

	char *name = user->name;
	free(user);
	return name;
}

/*-----------------------------------------------------------------------------
	Função para remover um utente da fila de espera, por desistencia
 */
static void user_remove(char *name) {
	if (NULL == head)
		return;
	User *prev = NULL;
	for (User *user = head; user != NULL; prev = user, user = user->next)
		if (strcmp(name, user->name) == 0){
			if (NULL == prev) {
				head = user->next;
				tail = NULL == head ? NULL : tail;
			}
			else {
				prev->next = user->next;
				tail = NULL == prev->next ? prev : tail;
			}
			free(user->name);
			free(user);
			return;
		}
}

/*-----------------------------------------------------------------------------
	Listar os utentes na fila de espera.
 */
void user_print() {
	if (NULL == head) {
		printf("Fila vazia\n");
		return;
	}
	int i = 1;
	for (User *user = head; user != NULL; user = user->next)
		printf("%d: %s, %ld\n", i++, user->name, time(NULL) - user->arrival);
}

/*-----------------------------------------------------------------------------
	Vazar a lista libertando toda a memória alocada.
 */
void user_leak_queue() {
	for (User *next, *p = head; p != NULL; p = next) {
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


