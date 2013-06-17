#include "linked_list.h"
void test_remove_from_empty(void){
	linked_list * head = NULL;
	head = remove_node(head, 10);
	display(head);
	head = insert(head, 10);
	display(head);
}

void test_remove_non_existent(void){
	linked_list * head = NULL;
	head = insert(head, 10);
	display(head);
	head = remove_node(head, 0);
	display(head);
}
void test_remove_all(void){
	linked_list * head = NULL;
	head = insert(head, 10);
	display(head);
	head = remove_node(head, 10);
	display(head);
	head = insert(head, 20);
	head = remove_node(head, 20);
	display(head);
	head = insert(head, 30);
	head = insert(head, 40);
	display(head);
	head = remove_node(head, 40);
	display(head);
	head = remove_node(head, 30);
	display(head);
}
void general_test(void){
	linked_list * head = NULL;
	head = insert(head, 10);
	display(head);
	head = insert(head, 20);
	head = insert(head, 30);
	head = insert(head, 40);
	head = insert(head, 50);
	printf("Found at %d\n", find(head, 10));
	printf("Found at %d\n", find(head, 20));
	printf("Found at %d\n", find(head, 40));
	display(head);
	head = remove_node(head, 10);
	display(head);
	head = remove_node(head, 40);
	display(head);
	head = insert(head, 60);
	insert_after(head->next->next,55);
	head = insert(head, 70);
	head = insert(head, 80);
	display(head);

}
int main(int argc, char * argv[]){
	int val = atoi(argv[1]);
	if(argc < 2){
		puts("Enter an argument from 0 to 3 indicating\
		which test case to run");
		return -1;
	}
	switch(val){
		case 0:
			test_remove_non_existent();
			break;
		case 1:
			test_remove_from_empty();
			break;
		case 2:
			test_remove_all();
			break;
		case 3:
			general_test();
			break;
		default:
			puts("Enter a test case between 0 to 3");
	}
}
