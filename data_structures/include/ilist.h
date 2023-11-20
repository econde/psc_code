#ifndef ILIST_H
#define ILIST_H

typedef struct Ilist_node {
	struct Ilist_node *next, *prev;
} Ilist_node;

#define STATIC_LIST(name)	Ilist_node name = {&name, &name};

void ilist_init(Ilist_node *node);

Ilist_node *ilist_create();

void ilist_destroy(Ilist_node *list);

void ilist_insert_rear(Ilist_node *list, Ilist_node *new_node);

void ilist_insert_front(Ilist_node *list, Ilist_node *new_node);

Ilist_node * ilist_remove_rear(Ilist_node *list);

Ilist_node * ilist_remove_front(Ilist_node *list);

void ilist_remove(Ilist_node *node);

int ilist_empty(Ilist_node *list);

Ilist_node * ilist_front(Ilist_node *list);

Ilist_node * ilist_rear(Ilist_node *list);

Ilist_node * ilist_sentinel(Ilist_node *list);

Ilist_node * ilist_search(Ilist_node *list, const void *key,
						int (*cmp)(Ilist_node *, const void *));

void ilist_foreach(Ilist_node *node, void (*do_it)(Ilist_node *));

int ilist_size(Ilist_node *list);

#endif
