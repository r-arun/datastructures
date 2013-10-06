#include <stdlib.h>

struct doubly_linked_list{
	int data;
	struct doubly_linked_list * prev;
	struct doubly_linked_list * next;
};

typedef struct doubly_linked_list dll;

static dll * create_dll_node(int value){
	dll * new_node = (dll *) malloc(sizeof(dll));
	new_node->data = value;
	new_node->prev = new_node->next = NULL;
	return new_node;
}

dll * push_front(dll * head,int value){
	if(!head){
		return create_dll_node(value);
	}
	dll * new_node = create_dll_node(value);
	new_node->next = head;
	head->prev = new_node;
	return new_node;
}

void print_list(dll * head){
	while(head){
		printf("%d ->", head->data);
		head = head->next;
	}
	printf("[]\n");
}
