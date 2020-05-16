/*	Instituto Superior de Engenharia de Lisboa
	Ezequiel Conde, 2015
*/
#include <stdlib.h>
#include <assert.h>

#include "listdi.h"

void list_init(List_node *node) {
	node->next = node->prev = node;
}

List_node *list_create() {
	List_node *node = malloc(sizeof(List_node));
	if (node == 0)
		return 0;
	list_init(node);
	return node;
}

void list_destroy(List_node *node) {
	assert(node);
	free(node);
}

/* node - elemento de referência; new_node - novo elemento */

void list_insert_rear(List_node *node, List_node *new_node) {
	assert(node && new_node);
	new_node->next = node->next;
	new_node->prev = node;
	node->next->prev = new_node;
	node->next = new_node;
}

void list_insert_front(List_node *node, List_node *new_node) {
	assert(node && new_node);
	new_node->prev = node->prev;
	new_node->next = node;
	node->prev->next = new_node;
	node->prev = new_node;
}

List_node *list_remove_rear(List_node *node) {
	assert(node);
	List_node *aux = node->next;
	node->next = node->next->next;
	aux->next->prev = aux->prev;
	aux->next = 0;
	return aux;
}

List_node *list_remove_front(List_node *node) {
	assert(node);
	List_node *aux = node->prev;
	node->prev = node->prev->prev;
	aux->prev->next = aux->next;
	aux->next = 0;
	return aux;
}

void list_remove(List_node *node) {
	assert(node);
	if (node->next == node)
		return;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	node->next = node->prev = node;
}

int list_empty(List_node *node) {
	assert(node);
	return node->next == node;
}

List_node *list_front(List_node *node) {
	assert(node);
	return node->prev;
}

List_node *list_rear(List_node *node) {
	assert(node);
	return node->next;
}

List_node *list_sentinel(List_node *node) {
	assert(node);
	return node;
}

List_node *list_search(List_node *node, const void *key,
						int (*cmp)(List_node *, const void *)) {
	for (List_node *p = node->next; p != node; p = p->next)
		if (cmp(p, key) == 0)
				return p;
	return NULL;
}

void list_foreach(List_node *node, void (*opr)(List_node *)) {
	for (List_node *next, *p = node->next; p != node; p = next) {
		next = p->next;
		opr(p);
	}
}

int list_size(List_node *node) {
	int counter = 0;
	List_node * link;
	for (link = list_front(node);
			link != list_sentinel(node); link = list_front(link))
		counter++;
	return counter;
}
