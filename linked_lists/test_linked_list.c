#include "linked_list.h"
void test_remove_from_empty(void){
	linked_list * head = NULL;
	head = remove_node(head, 10);
	display(head);
	head = append(head, 10);
	display(head);
}

void test_remove_non_existent(void){
	linked_list * head = NULL;
	head = append(head, 10);
	display(head);
	head = remove_node(head, 0);
	display(head);
}
void test_remove_all(void){
	linked_list * head = NULL;
	head = append(head, 10);
	display(head);
	head = remove_node(head, 10);
	display(head);
	head = append(head, 20);
	head = remove_node(head, 20);
	display(head);
	head = append(head, 30);
	head = append(head, 40);
	display(head);
	head = remove_node(head, 40);
	display(head);
	head = remove_node(head, 30);
	display(head);
}
void general_test(void){
	linked_list * head = NULL;
	head = append(head, 10);
	display(head);
	head = append(head, 20);
	head = append(head, 30);
	head = append(head, 40);
	head = append(head, 50);
	printf("Found at %d\n", find(head, 10));
	printf("Found at %d\n", find(head, 20));
	printf("Found at %d\n", find(head, 40));
	display(head);
	head = remove_node(head, 10);
	display(head);
	head = remove_node(head, 40);
	display(head);
	head = append(head, 60);
	insert_after(head->next->next,55);
	head = append(head, 70);
	head = append(head, 80);
	display(head);

}
void test_insert_at_beginning(void){
	linked_list * head = NULL;
	head = insert_at_beginning(head, 10);
	display(head);
	head = insert_at_beginning(head, 20);
	display(head);
	head = insert_at_beginning(head, 30);
	display(head);
}
int main(int argc, char * argv[]){
	int test_arr[]={10,20,30,40,45,50,55,60};
	linked_list * head;
	if(argc < 2){
		puts("Enter an argument from 0 to 5 indicating\
		which test case to run");
		return -1;
	}
	int val = atoi(argv[1]);
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
		case 4:
			head = construct(test_arr, 8);
			display(head);
			break;
		case 5:
			test_insert_at_beginning();
			break;
		default:
			puts("Enter a test case between 0 to 5");
	}
}
