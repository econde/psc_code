/*	Instituto Superior de Engenharia de Lisboa
	Ezequiel Conde, 2015
	
	Lista instrusiva duplamente ligada com sentinela.
*/
#ifndef LISTDI_H
#define LISTDI_H

typedef struct List_node {
	struct List_node *next, *prev;
} List_node;

#define STATIC_LIST(name)	List_node name = {&name, &name};

void list_init(List_node *node);

List_node *list_create();

void list_destroy(List_node *node);

void list_insert_rear(List_node *node, List_node *new_node);

void list_insert_front(List_node *node, List_node *new_node);

List_node * list_remove_rear(List_node *node);

List_node * list_remove_front(List_node *node);

void list_remove(List_node *node);

int list_empty(List_node *node);

List_node * list_front(List_node *node);

List_node * list_rear(List_node *node);

List_node * list_sentinel(List_node *node);

List_node * list_search(List_node *node, const void *key,
						int (*cmp)(List_node *, const void *));

void list_foreach(List_node *node, void (*do_it)(List_node *));

int list_size(List_node *node);

#endif
