#ifndef ILIST_H
#define ILIST_H

typedef struct IList_node {
	struct IList_node *next, *prev;
} IList_node;

#define STATIC_LIST(name)	IList_node name = {&name, &name};

void ilist_init(IList_node *node);

IList_node *ilist_create();

void ilist_destroy(IList_node *list);

void ilist_insert_rear(IList_node *list, IList_node *new_node);

void ilist_insert_front(IList_node *list, IList_node *new_node);

IList_node * ilist_remove_rear(IList_node *list);

IList_node * ilist_remove_front(IList_node *list);

void ilist_remove(IList_node *node);

int ilist_empty(IList_node *list);

IList_node * ilist_front(IList_node *list);

IList_node * ilist_rear(IList_node *list);

IList_node * ilist_sentinel(IList_node *list);

IList_node * ilist_search(IList_node *list, const void *key,
						int (*cmp)(IList_node *, const void *));

void ilist_foreach(IList_node *node, void (*do_it)(IList_node *));

int ilist_size(IList_node *list);

#endif
