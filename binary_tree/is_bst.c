#include <stdio.h>
#include "binary_tree.h"
#define TRUE 1
#define FALSE 0

int check_binary_search_tree(bin_tree * node){
	if(node == NULL) return TRUE;
	if(node->left){
		if(node->data < node->left->data) return FALSE;
	}
	if(node->right){
		if(node->data > node->right->data) return FALSE;
	}
	if(check_binary_search_tree(node->left) &&
		check_binary_search_tree(node->right))
		return TRUE;
	else
		return FALSE;
}

int main(){
	bin_tree * r1 = create_binary_tree("input");	
	bin_tree * r2 = create_binary_tree("bst.in");
	//inorder(r1);
	puts("");
	printf("%d\n\n",check_binary_search_tree(r1));
	//inorder(r2);
	puts("");
	printf("%d\n\n",check_binary_search_tree(r2));
}
