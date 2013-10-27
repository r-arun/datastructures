#include <stdio.h>
#include "binary_tree.h"
#define TRUE 1
#define FALSE 0

struct pair{
	int first;
	int second;
};

int is_valid(struct pair num){
	printf("%d, %d\n", num.first, num.second);
	return num.first <= num.second;
}
struct pair check_binary_search_tree(bin_tree * node){
	struct pair result;
	result.first = 1;
	result.second = -1;
	struct pair lst;
	struct pair rst;
	if(node == NULL) return result;
	if(node) printf("Tree: %d\n", node->data);
	if(node->left){
		if(!is_valid(lst = check_binary_search_tree(node->left)))
			return result;
		if(lst.second >= node->data) return result;
	}
	if(node->right){
		if(!is_valid(rst = check_binary_search_tree(node->right)))
			return result;
		if(rst.first < node->data) return result;
	}
	if(!node->left)
		result.first = node->data;
	else
		result.first = lst.first;
	if(!node->right)
		result.second = node->data;
	else
		result.second = rst.second;
	return result;
}

int main(){
	bin_tree * r1 = create_binary_tree("input/non-bst.in");	
	bin_tree * r2 = create_binary_tree("input/bst2.in");
	bin_tree * r3 = create_binary_tree("input/is_bst.in");
	inorder(r1);
	puts("");
	pretty_print(r1);
	printf("%d\n\n",is_valid(check_binary_search_tree(r1)));
	inorder(r2);
	puts("");
	pretty_print(r2);
	printf("%d\n\n",is_valid(check_binary_search_tree(r2)));
	inorder(r3);
	puts("");
	pretty_print(r3);
	printf("%d\n\n",is_valid(check_binary_search_tree(r3)));
}
