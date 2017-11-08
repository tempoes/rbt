#include "rbtree.h"

void print_node(rbtree *current) {
	printf("%s-%d ", current->value, current->color);
}

void rbtree_print_dfs(rbtree* root, void (*print_node)(rbtree*)) {
	if (root) {
		print_node(root);
		rbtree_print_dfs(root->left, print_node);
		printf("\n");
		rbtree_print_dfs(root->right, print_node);
	}
}

rbtree * rbtree_left_rotate(rbtree * root, rbtree * node) {
	rbtree * right = node->right; // находим y, в контексте right
	node->right = right->left; // левый потомок right становится правым потомком node

	if (right->left != NullNode)  // если левый потомок right не является листом(NullNode), то связываем его
		right->left->p = node; //(уже узел т. е. поддерево) с node

	right->p = node->p; // связываем right отцом node
	
	if (node->p == NullNode) {   // если отец = NullNode, то отец right - корень 
		root = right;
	}
	else if (node == node->p->left) { // если node - левое поддерево
		node->p->left = right;
	}
	else {
		node->p->right = right; //  если node - правое поддерево
	}
	right->left = node;  // node становится левым дочерним в отношении right
	node->p = right;

	return root;
}

rbtree * rbtree_right_rotate(rbtree * root, rbtree * node) {
	rbtree * left = node->left;
	node->left = left->right;

	if (left->right != NullNode)
		left->right->p = node;
	
	left->p = node->p;
	
	if (node->p == NullNode)
		root = left;
	else if (node == node->p->right) {
		node->p->right = left;
	}
	else {
		node->p->left = left;
	}
	
	left->right = node;
	node->p = left;
	
	return root;
}

rbtree * rbtree_fixup_add(rbtree * root, rbtree * node) {
	rbtree * uncle;
	
	while (node->p->color == RED && node != root) {
		if ( node->p == node->p->p->left){
			uncle = node->p->p->right;
			if (uncle->color == RED) {
				node->p->color = BLACK;
				uncle->color = BLACK;
				node->p->p->color = RED;
				node = node->p->p;
			}
			else {
				if (node == node->p->right) {
					node = node->p;
					root = rbtree_left_rotate(root, node);
					printf("left rotate\n");
				}
				
				node->p->color = BLACK;
				node->p->p->color = RED;
				root = rbtree_right_rotate(root, node->p->p);
				printf("right rotate\n");
			}
		}
		else {
			uncle = node->p->p->left;
			if (uncle->color == RED) {
				node->p->color = BLACK;
				uncle->color = BLACK;
				node->p->p->color = RED;
				node = node->p->p;
			}
			else {
				if (node == node->p->left) {
					node = node->p;
					root = rbtree_right_rotate(root, node);
					printf("right rotate\n");
				}
				node->p->color = BLACK;
				node->p->p->color = RED;
				root = rbtree_left_rotate(root, node->p->p);
				printf("left rotate\n");
			}
		}

	}
	root->color = BLACK;
	return root;
}

rbtree * rbtree_add(rbtree * root, int key, char * value) {
	rbtree * parent = NullNode;
	rbtree * node = NullNode;
	for(node = root; node != NullNode && node != NULL; ) {
		parent = node;
		if(key < node->key) {
			node = node->left;
		}
		else if ( key > node->key) {
			node = node->right;
		}
		else
			return root;
	}
	node = malloc(sizeof(*node));
	if (node == NULL)
		return NULL;

	node->key = key; 
	node->value = value; 

	node->color = RED;
	node->p = parent;
	node->left = NullNode;
	node->right = NullNode;

	if(parent != NullNode) {
		if (key < parent->key)
			parent->left = node;
		else
			parent->right = node;
	} else {
		root = node;
	}
	return rbtree_fixup_add(root, node);
}

rbtree * rbtree_lookup (rbtree * node, int key) {
	while (node != NULL) {
		if (key == node->key) {
			return node; 
		}
		else if (key < node->key) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	return node;
}


rbtree * rbtree_delete_fixup(rbtree * root, rbtree * node) {
	rbtree * w;
	while ( node != root && node->color == BLACK ) {
		if ( node == node->p->left ) {
			w = node->p->right;
			if ( w->color == RED) {
				w->color = BLACK;
				node->p->color = RED;
				root = rbtree_left_rotate(root, node->p);
				w = node->p->right;
			}
			if ( w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				node = node->p;
			}
			else {
				if ( w->right->color == BLACK ) {
					w->left->color  = BLACK;
					w->color = RED;
					root = rbtree_right_rotate(root, w);
					w = node->p->right;
				}
				w->color = node->p->color;
				node->p->color = BLACK;
				w->right->color = BLACK;
				root = rbtree_left_rotate(root, node->p);
				node = root;
			}
		}
		else {
			w = node->p->left;
			if ( w->color == RED) {
				w->color = BLACK;
				node->p->color = RED;
				root = rbtree_right_rotate(root, node->p);
				w = node->p->left;
			}
			if ( w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				node = node->p;
			}
			else {
				if ( w->left->color == BLACK ) {
					w->right->color  = BLACK;
					w->color = RED;
					root = rbtree_left_rotate(root, w);
					w = node->p->left;
				}
				w->color = node->p->color;
				node->p->color = BLACK;
				w->left->color = BLACK;
				root = rbtree_right_rotate(root, node->p);
				node = root;
			}
		}
	}
	node->color = BLACK;
	return root;
}

rbtree * rbtree_min(rbtree *tree)
{
	if (tree == NULL)
		return NULL;

	while ((tree->left != NULL) && (tree->left != NullNode))
		tree = tree->left;
	return tree;
}

rbtree * rbtree_max(rbtree *tree)
{
	if (tree == NULL)
		return NULL;

    while ((tree->right != NULL) && (tree->right != NullNode))
		tree = tree->right;
	return tree;
}


rbtree * rbtree_delete(rbtree * root, int key) {
	rbtree * node, * y, * x; 
	node = rbtree_lookup(root, key);
	y = node;
	int y_color = y->color;
	if (node->left == NullNode) {
		x = node->right;
		root = rbtree_transplant(root, node, node->right);
	}
	else if (node->right == NullNode) {
		x = node->left;
		root = rbtree_transplant(root, node, node->left);
	}
	else {
		y = rbtree_min(node->right);
		y_color = y->color;
		x = y->right;
		if (y->p == node)
			x->p = y;
		else {
			root = rbtree_transplant(root, y, y->right);
			y->right = node->right;
			y->right->p = y;
		}
		root = rbtree_transplant(root, node, y);
		y->left = node->left;
		y->left->p = y;
		y->color = node->color;
	}
	if (y_color == BLACK)
		root = rbtree_delete_fixup(root, x);
	free(node);
	return root;
}

rbtree * rbtree_transplant(rbtree * root, rbtree * u, rbtree * v) {
	if (u->p == NullNode)
		root = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;

	v->p = u->p;
	return root;
}

void rbtree_free(struct rbtree *tree)
{
   	if (tree == NullNode)
   		return;
    if (tree->left != NullNode) {
        rbtree_free(tree->left);
    }
    if (tree->right != NullNode) {
        rbtree_free(tree->right);
    }
    free(tree);
}
