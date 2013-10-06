#include "binary_tree.h"
#include "doubly_linked_list.h"
#include <stdio.h>

dll* binary_tree_to_dll(bin_tree * root, dll * list_node){
	if(root->right)
		list_node = binary_tree_to_dll(root->right, list_node);
	list_node = push_front(list_node, root->data);
	if(root->left)
		list_node = binary_tree_to_dll(root->left, list_node);
	return list_node;
}

dll * convert_binary_tree_to_dll(bin_tree * root){
	dll * head = NULL;
	if(!root) return NULL;
	return binary_tree_to_dll(root, head);
}

int main(){
	/*
	* Pass the file containing, a representation of the tree. The
	* function returns the root.
	**/
	bin_tree * root = create_binary_tree("input/dll_test.txt");
	puts("");
	inorder(root);
	puts("");
	pretty_print(root);
	dll * result = convert_binary_tree_to_dll(root);
	print_list(result);
}
