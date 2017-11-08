#include "rbtree.h"

int main(int argc, char ** argv) {
	rbtree * tree = NULL;
	
	rbtree_print_dfs(tree, print_node);
	tree = rbtree_add(tree, 10, "10");
	rbtree_print_dfs(tree, print_node);
	tree = rbtree_add(tree, 5, "5");
	rbtree_print_dfs(tree, print_node);
	tree = rbtree_add(tree, 3, "3");
	rbtree_print_dfs(tree, print_node);
	tree = rbtree_add(tree, 11, "11");
	rbtree_print_dfs(tree, print_node);
	tree = rbtree_add(tree, 12, "12");
	rbtree_print_dfs(tree, print_node);
	tree = rbtree_add(tree, 6, "6");
	rbtree_print_dfs(tree, print_node);
	tree = rbtree_add(tree, 8, "8");
	rbtree_print_dfs(tree, print_node);
	tree = rbtree_add(tree, 9, "9");
	rbtree_print_dfs(tree, print_node);
	
	/*tree = rbtree_delete(tree, 10);
	tree = rbtree_delete(tree, 5);
	tree = rbtree_delete(tree, 3);
	tree = rbtree_delete(tree, 11);
	tree = rbtree_delete(tree, 12);
	tree = rbtree_delete(tree, 6);
	tree = rbtree_delete(tree, 8);
	tree = rbtree_delete(tree, 9);*/
	//rbtree_print_dfs(tree, print_node);

	rbtree_free(tree);
	return 0;
}