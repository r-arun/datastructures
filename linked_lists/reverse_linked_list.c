#include "linked_list.h"

linked_list * reverse(linked_list * node){
	if(!node)
		return node;
	if(!node->next)
		return node;
	linked_list * next_successor = node->next;
	node->next = NULL;
	linked_list * prev_head = reverse(next_successor);
	next_successor->next = node;
	return prev_head;
}
int main(){
	int arr[] = {10,20,30,40,50,60,70};
	linked_list * head = construct(arr, 7);
	display(head);
	linked_list * reversed = reverse(head);
	display(reversed);
}
