#ifndef LISTD_H
#define LISTD_H

typedef struct List_node {
	struct List_node *next, *prev;
	void *data;
} List_node;

void list_init(List_node *p);

List_node *list_create();

void list_destroy(List_node *p);

int list_insert_rear(List_node *p, void *data);

int list_insert_front(List_node *p, void *data);

void list_remove(List_node *node);

void ist_remove_rear(List_node *p);

void list_remove_front(List_node *p);

int list_insert_sort(List_node *node, void *data, 
	int (*cmp)(const void*, const void*));

void list_foreach(List_node *node, void (*do_it)(void*));

List_node *list_search(List_node *node, void *data,
	int (*cmp)(const void*, const void*));

List_node *list_front(List_node *node);

List_node *list_rear(List_node *node);

int list_empty(List_node *node);

void * list_data(List_node *node);

#endif
