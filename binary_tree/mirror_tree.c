#include "binary_tree.h"
#include <stdio.h>

bin_tree*  mirror(bin_tree * root){
	if(!root)
		return NULL;
	mirror(root->left);
	mirror(root->right);
	bin_tree * temp = root->left;
	root->left = root->right;
	root->right = temp;
	return root;
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
	bin_tree * new_root = mirror(root);
	puts("");
	preorder(new_root);
	puts("");
	inorder(new_root);
	puts("");
	postorder(new_root);
	puts("");
	pretty_print(new_root);
}
