#include <stdio.h>
#include <stdlib.h>
struct llist{
	int data;
	struct llist * next;
};

typedef struct llist linked_list;

static linked_list * create_node(int value){
	linked_list * node = (linked_list *)malloc(sizeof(linked_list));
	node->data = value;
	node->next = NULL;
	return node;
}

linked_list* append(linked_list * head, int value){
	//inserts an element at the end of a list
	if(!head){
		head = create_node(value);
		printf("Inserted \n");
		return head;
	}
	linked_list * list = head;
	linked_list * node = create_node(value);
	while(list->next) list = list->next;
	//head->next is empty
	list->next = node;
	return head;
}

linked_list* insert_at_beginning(linked_list * head, int value){
	linked_list * node = create_node(value);
	node->next = head;
	return node;
}

void insert_after(linked_list * pos, int value){
	//Inserts the value of the node pointed by pos
	linked_list * node = create_node(value);
	node->next = pos->next;
	pos->next = node;
}

static int find_wrong(linked_list * head, int value){
	/*wrong assumption that malloc provides contiguous
	*allocations
	*Do not make it in your code, for this purpose
	*/
	linked_list * list = head;
	while(list){
		if(list->data == value) return list-head;
		list = list->next;
	}
	return -1;
}

int find(linked_list * head, int value){
	//returns the 0-indexed position at which the 
	//element is found. Or returns -1, if not found.
	int cnt = 0;
	while(head){
		if(head->data == value) return cnt;
		head = head->next;
		++cnt;
	}
	return -1;
}

linked_list * remove_node(linked_list * head, int value){
	linked_list * node = head;
	if(!head) return head;
	if(head->data == value){
		linked_list * node = head;
		head = head->next;
		free(node);
		return head;
	}
	while(node->next){
		if(node->next->data == value){
			linked_list * rem = node->next;
			node->next = rem->next;
			free(rem);
			break;
		}
		node = node->next;
	}
	return head;
}

void display(linked_list * head){
	//display a list from beginning till end
	linked_list * list = head;
	if(!list){
		printf("Empty List");
	}
	while(list){
		printf("%d", list->data);
		if(list->next)
			printf("-> ");
		list = list->next;
	}
	printf("\n");
}

linked_list * construct(int * value, int size){
	linked_list * head = NULL;
	while(size--){
		head = append(head,*(value++));
	}
	return head;
}

int * cmd_to_int_arr(int argc, char * argv[]){
	int * arr = NULL;
	int size = argc - 1;	
	if(size > 0){
		arr = (int *) malloc(size * sizeof(int));
		int i = 1;
		for(; i <= size; ++i){
			arr[i-1] = atoi(argv[i]);
		}
	}
	return arr;
}
