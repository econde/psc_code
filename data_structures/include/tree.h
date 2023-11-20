#ifndef TREE_H
#define TREE_H

typedef struct Tree_node {
	struct Tree_node *left, *right;
	void *data;
} Tree_node;

void tree_destroy(Tree_node *);

Tree_node *tree_insert(Tree_node *node, void *data,
					int (*cmp)(const void *, const void *));

Tree_node *tree_search(Tree_node *node, void *key,
					int (*cmp)(const void *, const void *));

void tree_foreach(Tree_node *node, void (*do_it)(void*));

size_t tree_size(Tree_node *node);

int tree_depth(Tree_node *node);

void *tree_data(Tree_node *);

#endif





