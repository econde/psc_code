#ifndef SLIST_H
#define SLIST_H

#define STATIC_LIST(name)	SList_node *name = NULL;

typedef struct Node {
	struct Node *next;
	void *data;
} SList_node;

//static inline void slist_init(SList_node *list) { list->next = list; }

void slist_destroy(SList_node *list);

SList_node *slist_insert(SList_node *list, void *data);

SList_node *slist_remove(SList_node *list, SList_node *node);

SList_node *slist_insert_sort(SList_node *list, void *data,
	int (*cmp)(const void *, const void *));

void slist_foreach(SList_node *list, void(*do_it)(void*));

SList_node *slist_search_sort(SList_node *list, const void *data,
	int (*fcmp)(const void *, const void *));

SList_node *slist_search(SList_node *list, const void *data,
	int (*cmp)(const void *, const void *));

int slist_size(SList_node *);

void *slist_data(SList_node *);

int slist_empty(SList_node *);

#endif