/*	Instituto Superior de Engenharia de Lisboa
	Ezequiel Conde, 2015
*/
#include <stdlib.h>
#include <assert.h>

#include "ilist.h"

void ilist_init(Ilist_node *node) {
	node->next = node->prev = node;
}

Ilist_node *ilist_create() {
	Ilist_node *node = malloc(sizeof(Ilist_node));
	if (node == 0)
		return 0;
	ilist_init(node);
	return node;
}

void ilist_destroy(Ilist_node *list) {
	assert(list);
	free(list);
}

/* node - elemento de referência; new_node - novo elemento */

void ilist_insert_front(Ilist_node *list, Ilist_node *new_node) {
	assert(list && new_node);
	new_node->next = list->next;
	new_node->prev = list;
	list->next->prev = new_node;
	list->next = new_node;
}

void ilist_insert_rear(Ilist_node *list, Ilist_node *new_node) {
	assert(list && new_node);
	new_node->prev = list->prev;
	new_node->next = list;
	list->prev->next = new_node;
	list->prev = new_node;
}

Ilist_node *ilist_remove_front(Ilist_node *list) {
	assert(list);
	Ilist_node *node = list->next;
	list->next = list->next->next;
	node->next->prev = node->prev;
	return node;
}

Ilist_node *ilist_remove_rear(Ilist_node *list) {
	assert(list);
	Ilist_node *node = list->prev;
	list->prev = list->prev->prev;
	node->prev->next = node->next;
	return node;
}

void ilist_remove(Ilist_node *node) {
	assert(node);
	if (node->next == node)
		return;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	node->next = node->prev = node;
}

int ilist_empty(Ilist_node *list) {
	assert(list);
	return list->next == list;
}

Ilist_node *ilist_rear(Ilist_node *node) {
	assert(node);
	return node->prev;
}

Ilist_node *ilist_front(Ilist_node *list) {
	assert(list);
	return list->next;
}

Ilist_node *ilist_sentinel(Ilist_node *list) {
	assert(list);
	return list;
}

Ilist_node *ilist_search(Ilist_node *list, const void *key,
						int (*cmp)(Ilist_node *, const void *)) {
	for (Ilist_node *p = list->next; p != list; p = p->next)
		if (cmp(p, key) == 0)
				return p;
	return NULL;
}

void ilist_foreach(Ilist_node *list, void (*do_it)(Ilist_node *)) {
	for (Ilist_node *next, *p = list->next; p != list; p = next) {
		next = p->next;
		do_it(p);
	}
}

int ilist_size(Ilist_node *list) {
	int counter = 0;
	Ilist_node * link;
	for (link = ilist_front(list);
			link != ilist_sentinel(list); link = ilist_front(link))
		counter++;
	return counter;
}
