#include "linked_list.h"
linked_list * reverse2(linked_list * node){
	linked_list * new_head = NULL;
	while(node){
		int value = node->data;
		node = remove_node(node, value);
		linked_list * new_node = create_node(value);
		new_node->next = new_head;
		new_head = new_node;
	}
}
int main(){
	int arr[] = {10,20,30,40,50,60,70};
	linked_list * head = construct(arr, 7);
	display(head);
	linked_list * reversed = reverse2(head);
	display(reversed);
}
