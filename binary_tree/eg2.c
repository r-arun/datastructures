#include "binary_tree.h"

int main(int argc, char * argv[]){
	//Pass the size of the tree. The function returns the root.
	bin_tree * root = create_random_binary_tree(9);
	preorder(root);
	puts("");
	inorder(root);
	puts("");
	postorder(root);
	puts("");
	pretty_print(root);
}
