#include "stack.h"
#include "binary_tree.h"
#include "doubly_linked_list.h"
#define LEFT 0
#define RIGHT 1

stack * find(bin_tree * root, bin_tree * node){
	stack * result = NULL;
	stack * dir = NULL;
	int direction[] = {LEFT, RIGHT};
	if(!root){
		return result;
	}
	bin_tree * n = root;
	do{
		if(n){
			result = push(result,(void *)n);
			dir = push(dir,(void *) direction);
			if(n == node) return result;
			n = n->left;
		}
		else{
			int *d = (int *)get_top(dir);
			dir = pop(dir);
			if(*d == LEFT){
				dir = push(dir, (void *) (direction+1));
				n = (bin_tree *) get_top(result);
				n = n->right;
			}
			else{
				result = pop(result);
				n = NULL;
			}
			if(!n && is_empty(result)){
				break;
			}
		}
	}while(1);
	return result;
}

bin_tree * lca(bin_tree * root, bin_tree * n1, bin_tree *n2){
	if(!root)
		return NULL;
	if(!n1 || !n2)
		return NULL;
	printf("Starts\n");
	stack * st = find(root, n1);
	print_stack(st);
	if(is_empty(st)) return NULL;
	while(!is_empty(st)){
		bin_tree * n = (bin_tree *) get_top(st);
		st = pop(st);
		stack * result = find(n, n2);
		if(!is_empty(result))
			return n;
	}
	return NULL;
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
