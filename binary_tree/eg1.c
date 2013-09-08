#include "binary_tree.h"
#include <stdio.h>

int main(){
	/*
	* Pass the file containing, a representation of the tree. The
	* function returns the root.
	**/
	bin_tree * root = create_binary_tree("input/bst.in");
	puts("");
	preorder(root);
	puts("");
	inorder(root);
	puts("");
	postorder(root);
	puts("");
	pretty_print(root);
}
