#include <stdlib.h>
#include "tree.h"

void tree_destroy(Tree_node *node) {
	if (node->left != NULL)
		tree_destroy(node->left);
	if (node->right != NULL)
		tree_destroy(node->right);
	free(node);
}

Tree_node *tree_search(Tree_node *node, void *data, 
                        int(*cmp)(void*, void*)) {
	if (NULL == node)
		return NULL;
	int cmp_result = cmp(node->data, data);
	if (cmp_result == 0)
		return node;
	if (cmp_result < 0) 
		return tree_search(node->right, data, cmp);
	else
		return tree_search(node->left, data, cmp);
}

Tree_node *tree_insert(Tree_node *root, void *data,
						int (*cmp)(void*, void*)) {
	if (NULL == root) {
		Tree_node *new_node = malloc(sizeof *new_node);
		if (NULL == new_node)
			return NULL;
		new_node->left = new_node->right = NULL;
		new_node->data = data;
		return new_node;
	}
	int cmp_result = cmp(root->data, data);
	if (cmp_result < 0)
		root->right = tree_insert(root->right, data, cmp);
	else if (cmp_result > 0)
		root->left = tree_insert(root->left, data, cmp);
	return root;
}

size_t tree_size(Tree_node *node)  {
	if (NULL == node)
		return 0;
	return tree_size(node->left) + tree_size(node->right) + 1;
}

void tree_foreach(Tree_node *node, void (*do_it)(void*)) {
	if (NULL == node)
		return;
	tree_foreach(node->left, do_it);
	do_it(node->data);
	tree_foreach(node->right, do_it);
}

static int max(int a, int b) {
	return (a > b) ? a : b;
}

int tree_depth(Tree_node *node) {
	if (node == NULL)
		return 0;
	return max(tree_depth(node->left), tree_depth(node->right)) + 1;
}

void *tree_data(Tree_node *node) {
	return node->data;
}
