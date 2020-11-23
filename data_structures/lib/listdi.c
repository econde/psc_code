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

void list_destroy(List_node *list) {
	assert(list);
	free(list);
}

/* node - elemento de referência; new_node - novo elemento */

void list_insert_front(List_node *list, List_node *new_node) {
	assert(list && new_node);
	new_node->next = list->next;
	new_node->prev = list;
	list->next->prev = new_node;
	list->next = new_node;
}

void list_insert_rear(List_node *list, List_node *new_node) {
	assert(list && new_node);
	new_node->prev = list->prev;
	new_node->next = list;
	list->prev->next = new_node;
	list->prev = new_node;
}

List_node *list_remove_front(List_node *list) {
	assert(list);
	List_node *node = list->next;
	list->next = list->next->next;
	node->next->prev = node->prev;
	return node;
}

List_node *list_remove_rear(List_node *list) {
	assert(list);
	List_node *node = list->prev;
	list->prev = list->prev->prev;
	node->prev->next = node->next;
	return node;
}

void list_remove(List_node *node) {
	assert(node);
	if (node->next == node)
		return;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	node->next = node->prev = node;
}

int list_empty(List_node *list) {
	assert(list);
	return list->next == list;
}

List_node *list_rear(List_node *node) {
	assert(node);
	return node->prev;
}

List_node *list_front(List_node *list) {
	assert(list);
	return list->next;
}

List_node *list_sentinel(List_node *list) {
	assert(list);
	return list;
}

List_node *list_search(List_node *list, const void *key,
						int (*cmp)(List_node *, const void *)) {
	for (List_node *p = list->next; p != list; p = p->next)
		if (cmp(p, key) == 0)
				return p;
	return NULL;
}

void list_foreach(List_node *list, void (*opr)(List_node *)) {
	for (List_node *next, *p = list->next; p != list; p = next) {
		next = p->next;
		opr(p);
	}
}

int list_size(List_node *list) {
	int counter = 0;
	List_node * link;
	for (link = list_front(list);
			link != list_sentinel(list); link = list_front(link))
		counter++;
	return counter;
}
