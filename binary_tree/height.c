#include "binary_tree.h"

#define max(a,b) ((a>b)?a:b)
int height(bin_tree * root){
	if(!root) return 0;
	int left_height = height(root->left);
	int right_height = height(root->right);
	int height = left_height;
	if(left_height < right_height)
		height = right_height;
	return height + 1;
}

int main(int argc, char * argv[]){
	int i;
	bin_tree * root = create_binary_tree(argv[1]);
	printf("%d\n", height(root));
}
