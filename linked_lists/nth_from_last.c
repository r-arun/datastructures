#include "linked_list.h"
//2.2 Cracking Coding Interview

linked_list * nth_from_end(linked_list * head, int n){
	linked_list * res = head;
	while(n-- && head)
		head = head->next;
	if(!head) return NULL;
	while(head->next){
		head = head->next;
		res = res->next;
	}
	return res;
}

int main(int argc, char * argv[] ){

	/*Input format space separated list of elements followed by the nth element
	* from the end. 
	* Eg: 1 4 7 8 1 
	* In the list 1-> 4-> 7-> 8, you look for the 1st element (0-base) from the
	* end. The answer return is 7.
	*/
	int size = argc - 2;
	if(argc <= 1) return 0;
	int n = atoi(argv[argc - 1]);
	if(n < 0) return 0;
	int * arr = cmd_to_int_arr(argc - 1, argv);
	linked_list * head = construct(arr, size);
	display(head);
	linked_list * res = nth_from_end(head, n);
	if(res)
		printf("%d\n", res->data);
	else
		printf("No valid element\n");
	free(arr);
	return 0;
}
