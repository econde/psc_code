#ifndef LISTDI_H
#define LISTDI_H

typedef struct List_node {
	struct List_node *next, *prev;
} List_node;

#define STATIC_LIST(name)	List_node name = {&name, &name};

void list_init(List_node *node);

List_node *list_create();

void list_destroy(List_node *list);

void list_insert_rear(List_node *list, List_node *new_node);

void list_insert_front(List_node *list, List_node *new_node);

List_node * list_remove_rear(List_node *list);

List_node * list_remove_front(List_node *list);

void list_remove(List_node *node);

int list_empty(List_node *list);

List_node * list_front(List_node *list);

List_node * list_rear(List_node *list);

List_node * list_sentinel(List_node *list);

List_node * list_search(List_node *list, const void *key,
						int (*cmp)(List_node *, const void *));

void list_foreach(List_node *node, void (*do_it)(List_node *));

int list_size(List_node *list);

#endif
