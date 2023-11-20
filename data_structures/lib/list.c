#include <stdlib.h>
#include <assert.h>
#include "list.h"

void list_init(List_node *node) {
	node->next = node->prev = node;
}

List_node *list_create() {
	List_node * node = malloc(sizeof(List_node));
	if (node == 0)
		return 0;
	list_init(node);
	return node;
}

void list_destroy(List_node *list) {
	assert(list);
	for (List_node *next, *node = list->next; node != list; node = next) {
		next = node->next;
		free(node);
	}
	free(list);
}

int list_insert_sort(List_node *node, void *data,
					 int (*comp)(const void*, const void*)) {
	List_node *p = list_search(node, comp, data);
	return list_insert_rear(p, data);
}

List_node *list_search(List_node *list,
		int (*predicate)(const void *, const void *), const void *context) {
	for(List_node *p = list->next; p != list; p = p->next)
		if (predicate(p->data, context))
			return p;
	return NULL;
}

int list_insert_front(List_node *node, void *data) {
	List_node *new_node = malloc(sizeof(List_node));
	if (new_node == NULL)
		return 0;
	new_node->data = data;

	new_node->next = node->next;
	new_node->prev = node;
	node->next->prev = new_node;
	node->next = new_node;
	return 1;
}

int list_insert_rear(List_node *node, void *data) {
	List_node *new_node = malloc(sizeof(List_node));
	if (new_node == NULL)
		return 0;
	new_node->data = data;

	new_node->prev = node->prev;
	new_node->next = node;
	node->prev->next = new_node;
	node->prev = new_node;
	return 1;
}

void list_remove(List_node *node) {
	node->next->prev = node->prev;
	node->prev->next = node->next;
	free(node);
}

void list_remove_front(List_node *node) {
	list_remove(node->next);
}

void list_remove_rear(List_node *node) {
	list_remove(node->prev);
}

void list_foreach(List_node *node, void (*do_it)(void*)) {
	for (List_node *p = node->next; p != node; p = p->next)
		do_it(p->data);
}

List_node *list_front(List_node *node) {
	return node->next;
}

List_node *list_rear(List_node *node) {
	return node->prev;
}

void *list_data(List_node *node) {
	return node->data;
}

int list_empty(List_node *node) {
	return node->next == node;
}

size_t list_size(List_node *list) {
	size_t size = 0;
	for (List_node *p = list->next; p != list; p = p->next)
		size++;
	return size;
}
