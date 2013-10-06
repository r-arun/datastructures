#include "binary_tree.h"
#include "doubly_linked_list.h"
#include <stdio.h>

bin_tree * lca(bin_tree * root, bin_tree * n1, bin_tree *n2){
	if(!root)
		return NULL;
	if(!n1 || !n2)
		return NULL;
	if(root == n1 || root == n2){
		return root;
	}
	bin_tree * lnode = lca(root->left, n1, n2);
	bin_tree * rnode = lca(root->right, n1, n2);
	if(lnode && rnode) return root;
	if(lnode) return lnode;
	return rnode;
}

int main(){
	/*
	* Pass the file containing, a representation of the tree. The
	* function returns the root.
	**/
	bin_tree * root = create_binary_tree("input/lca.txt");
	bin_tree * e1 = root->right->right;
	if(e1)
		printf("e1 data %d \n", e1->data);
	bin_tree * e2 = root->right->left->right;
	if(e2)
		printf("e2 data %d \n", e2->data);
	pretty_print(root);
	puts("");
	bin_tree * result = lca(root, e1, e2);
	if(result)
		printf("%d %d %d", e1->data, e2->data, result->data);
	pretty_print(result);
}
