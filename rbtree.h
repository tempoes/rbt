#ifndef RBTREE_H
#define RBTREE_H

#define RED 0
#define BLACK 1

#include <stdlib.h>
#include <stdio.h>

typedef struct rbtree {
	int key;
	char * value;
	int color;

	struct rbtree * left;
	struct rbtree * right;
	struct rbtree * p;
} rbtree;

static rbtree EmptyNode = {0, 0, BLACK, NULL, NULL, NULL};
static rbtree * NullNode = &EmptyNode;

rbtree * rbtree_add(rbtree * root, int key, char * value); //
rbtree * rbtree_delete(rbtree * root, int key); //
rbtree * rbtree_lookup(rbtree * root, int key); //
rbtree * rbtree_min(rbtree * root); //
rbtree * rbtree_max(rbtree * root); //
rbtree * rbtree_delete_fixup(rbtree * root, rbtree * node); ///
rbtree * rbtree_transplant(rbtree * root, rbtree * u, rbtree * v); ///


void rbtree_free(rbtree * root);
void rbtree_print_dfs(rbtree* root, void (*print_node)(rbtree*));
void print_node(rbtree *current);

#endif