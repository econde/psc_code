#include <stdlib.h>
#include "slist.h"

void slist_destroy(SList_node *list) {
	for (SList_node *next, *p = list; p != NULL; p = next) {
		next = p->next;
		free(p);
	}
}

SList_node *slist_insert_sort(SList_node *list,
	int (*fcmp)(const void *, const void *), void *data) {
	SList_node *node = malloc(sizeof (*node));
	if (NULL == node)
		return NULL;
	node->data = data;
	node->next = NULL;
	if (list == NULL)						/*	Primeiro elemento */
		;
	else if (fcmp(list->data, data) > 0) {	/* Inserção antes do primeiro elemento */
		node->next = list;
	}
	else {
		SList_node *prev = list;		/* Primeiro elemento já verificado */
		SList_node *p;
		for (p = prev->next; p != NULL && fcmp(p->data, data) < 0; prev = p, p = p->next)
			;
		node->next = p;
		prev->next = node;
		return list;
	}
	return node;
}

SList_node *slist_insert(SList_node *list, void *data) {
	SList_node *node = malloc(sizeof (*node));
	if (NULL == node)
		return 0;
	node->data = data;
	node->next = list;
	return node;
}

SList_node *slist_remove_head(SList_node *list) {
	SList_node *next = list->next;
	free(list);
	return next;
}

SList_node *slist_remove(SList_node *list, SList_node *node) {
	if (node == NULL || list == NULL)
		return list;
	if (list == node) {
		list = node->next;
		free(node);			/* Remover o primeiro elemento */
	}
	else {
		SList_node *prev = list;
		for (SList_node *p = prev->next; p != NULL; prev = p, p = p->next)
			if (p == node) {
				prev->next = node->next;
				free(node);
			}
	}
	return list;
}

void slist_foreach(SList_node *list, void(*do_it)(void *, void *), void *context) {
	for (SList_node * p = list; p != NULL; p = p->next)
		do_it(p->data, context);
}

SList_node *slist_search_sort(SList_node *list,
							int (*fcmp)(const void *, const void *), const void *data) {
	for (SList_node *p = list; p != NULL; p = p->next) {
		int tmp = fcmp(p->data, data);
		if (tmp == 0)
			return p;
		else if (tmp > 0)
			return NULL;
	}
	return NULL;
}

SList_node *slist_search(SList_node *list, const void *data,
	int (*fcmp)(const void *, const void *)) {
	for (SList_node *p = list; p != NULL; p = p->next)
		if (fcmp(p->data, data) == 0)
			return p;
	return NULL;
}

int slist_size(SList_node *list) {
	int n = 0;
	for (SList_node *p = list; p != NULL; p = p->next, ++n)
		;
	return n;
}

void *slist_data(SList_node *node) {
	return node->data;
}

int slist_empty(SList_node *list) {
	return NULL == list;
}

