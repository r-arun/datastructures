#include "binary_tree.h"
#include <stdio.h>

int count(bin_tree * root){
	if(!root)
		return 0;
	return (count(root->left) + 1 + count(root->right));
}

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
	int cnt = count(root);
	printf("%d\n", cnt);
}
