#include "binary_tree.h"
#include <stdio.h>

int main(){
	int pre_order [] = {7, 12, 3, 4, 1, 2, 8, 6, 10};
	int in_order [] = {3, 12, 1, 4, 2, 7, 6, 8, 10};
	//bin_tree * root = insert(pre_order, in_order, 0, 9, 0, 9);
	bin_tree * root = create_binary_tree("bst.in");
	puts("");
	preorder(root);
	puts("");
	inorder(root);
	puts("");
	postorder(root);
	puts("");
}
