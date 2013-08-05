#include "binary_tree.h"

int count(bin_tree * root){
	if(!root) return 0;
	return count(root->left) + count(root->right) + 1;
}

int main(int argc, char * argv[]){
	int i;
	bin_tree * root = create_binary_tree(argv[1]);
	printf("%d\n", count(root));
}
