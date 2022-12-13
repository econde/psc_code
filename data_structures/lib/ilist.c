/*	Instituto Superior de Engenharia de Lisboa
	Ezequiel Conde, 2015
*/
#include <stdlib.h>
#include <assert.h>

#include "ilist.h"

void ilist_init(IList_node *node) {
	node->next = node->prev = node;
}

IList_node *ilist_create() {
	IList_node *node = malloc(sizeof(IList_node));
	if (node == 0)
		return 0;
	ilist_init(node);
	return node;
}

void ilist_destroy(IList_node *list) {
	assert(list);
	free(list);
}

/* node - elemento de referência; new_node - novo elemento */

void ilist_insert_front(IList_node *list, IList_node *new_node) {
	assert(list && new_node);
	new_node->next = list->next;
	new_node->prev = list;
	list->next->prev = new_node;
	list->next = new_node;
}

void ilist_insert_rear(IList_node *list, IList_node *new_node) {
	assert(list && new_node);
	new_node->prev = list->prev;
	new_node->next = list;
	list->prev->next = new_node;
	list->prev = new_node;
}

IList_node *ilist_remove_front(IList_node *list) {
	assert(list);
	IList_node *node = list->next;
	list->next = list->next->next;
	node->next->prev = node->prev;
	return node;
}

IList_node *ilist_remove_rear(IList_node *list) {
	assert(list);
	IList_node *node = list->prev;
	list->prev = list->prev->prev;
	node->prev->next = node->next;
	return node;
}

void ilist_remove(IList_node *node) {
	assert(node);
	if (node->next == node)
		return;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	node->next = node->prev = node;
}

int ilist_empty(IList_node *list) {
	assert(list);
	return list->next == list;
}

IList_node *ilist_rear(IList_node *node) {
	assert(node);
	return node->prev;
}

IList_node *ilist_front(IList_node *list) {
	assert(list);
	return list->next;
}

IList_node *ilist_sentinel(IList_node *list) {
	assert(list);
	return list;
}

IList_node *ilist_search(IList_node *list, const void *key,
						int (*cmp)(IList_node *, const void *)) {
	for (IList_node *p = list->next; p != list; p = p->next)
		if (cmp(p, key) == 0)
				return p;
	return NULL;
}

void ilist_foreach(IList_node *list, void (*opr)(IList_node *)) {
	for (IList_node *next, *p = list->next; p != list; p = next) {
		next = p->next;
		opr(p);
	}
}

int ilist_size(IList_node *list) {
	int counter = 0;
	IList_node * link;
	for (link = ilist_front(list);
			link != ilist_sentinel(list); link = ilist_front(link))
		counter++;
	return counter;
}
