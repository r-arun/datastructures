#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>

struct binary_tree{
	int data;
	struct binary_tree * left;
	struct binary_tree * right;
};

typedef struct binary_tree bin_tree;

static bin_tree * create_bin_tree_node(int value){
	bin_tree * node = (bin_tree*)malloc(sizeof(bin_tree));
	node->data = value;
	node->left = node->right = NULL;
	return node;
}

bin_tree * insert(int * pre_order, int * in_order, int start, int limit, int root_pos, int size){
	bin_tree * root = NULL;
	if(start >= limit) return NULL;
	root = create_bin_tree_node(pre_order[root_pos]);
	int left_pos = start;
	for(; left_pos < limit; ++left_pos){
		if(in_order[left_pos] == pre_order[root_pos]){
			break;
		}
	}
	int right_child = INT_MAX;
	int i,j;
	for(i = left_pos + 1; i < limit; ++i){
		for(j = 0; j < size; ++j){
			if(in_order[i] == pre_order[j]){
				if(right_child > j){
					right_child = j;
				}
				break;
			}
		}
	}
	root->left = insert(pre_order, in_order,  start, left_pos, root_pos+1,size);
	if(right_child < INT_MAX)
		root->right = insert(pre_order, in_order, left_pos+1, limit, right_child,size);
	return root;
}


void preorder(bin_tree *root){
	if(root){
		printf("%d\n",root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(bin_tree *root){
	if(root){
		inorder(root->left);
		printf("%d\n",root->data);
		inorder(root->right);
	}
}

void postorder(bin_tree *root){
	if(root){
		postorder(root->left);
		postorder(root->right);
		printf("%d\n",root->data);
	}
}

bin_tree * create_binary_tree(char * fname){
	int size;
	if(size <= 0) return NULL;
	FILE * fp = fopen(fname, "r");
	fscanf(fp,"%d", &size);	
	int * pre_order = (int *)malloc(sizeof(bin_tree) *size);
	int * in_order = (int *)malloc(sizeof(bin_tree) *size);
	int i = 0;
	for(; i <size;++i){
		fscanf(fp,"%d",&pre_order[i]);
	}
	int j = 0;
	for(; j <size;++j){
		fscanf(fp,"%d",&in_order[j]);
	}
	fclose(fp);
	bin_tree * root = insert(pre_order, in_order, 0, size, 0, size);
	free(pre_order);
	free(in_order);
	return root;
}
/*
//TODO random binary trees
int random_in_interval(int start, int limit){
	return limit-start * (1/rand()) + start;
}
void random_array(int * pre_order, int * in_order,int start, int limit, int root_pos, int size){
		
}
*/

struct linked_list{
	bin_tree * data;
	struct linked_list * next;
};

typedef struct linked_list node;

struct queue{
	node * front;
	node * rear;
};

struct queue * init_queue(){
	struct queue * ret = (struct queue *)malloc(sizeof(struct queue));
	if(!ret) return NULL;
	ret->front = NULL;
	ret->rear = NULL;
	return ret;
}

node * create_node(bin_tree * value){
	node * ret = (node *)malloc(sizeof(node));
	if(!ret) return NULL;
	ret->data = value;
	ret->next = NULL;
	return ret;
}

void enqueue(struct queue * q, bin_tree * value){
	if(!q) return;
	node * ret = create_node(value);
	if(!ret) return;
	if(!q->rear){
		q->rear = q->front = ret;
	}
	else{
		q->rear->next = ret;
		q->rear = ret;
	}
}

bin_tree * dequeue(struct queue * q){
	assert(q && q->front);
	bin_tree * val = q->front->data;
	node * del = q->front;
	if(q->rear == q->front){
		q->rear = NULL;	
	}
	q->front = q->front->next;
	free(del);
	return val;
}

void print_queue(struct queue * q){
	node * n = q->front;
	printf("\n");
	while(n){
		if(n->data)
			printf("%d\n", n->data->data);
		else
			printf("NULL\n");
		n = n->next;
	}
	printf("End of Queue\n\n");
}

static test_tree_queue(struct queue *q, bin_tree * root){
	enqueue(q, root);
	if(!root)
		return;
	test_tree_queue(q, root->left);
	test_tree_queue(q, root->right);
}

print_space(int space, int height){
	space = space/height;
	while(space--)
		printf(" ");
}

void visualize(bin_tree *root){
	if(!root){
		puts("Empty Tree");
	}
	struct queue * exp = init_queue();	
	struct queue * vis = init_queue();	
	enqueue(exp, root);
	int height = 0;
	do{
		++height;
		assert(exp->rear != NULL);
		printf("Queues %p %p\n", vis, exp);
		struct queue * t = exp;
		exp = vis;
		vis = t;
		//swap(&vis, &exp);
		while(vis->front != NULL){
			bin_tree * node = dequeue(vis);
			if(node){
				print_space(32, height);
				printf("%3d ", node->data);
				print_space(32/2, height);
				enqueue(exp, node->left);
				enqueue(exp, node->right);
			}
			else{
				print_space(32, height);
				printf("X");
				print_space(32/2, height);
			}
		}
		printf("\n");
		assert(vis->rear == NULL);
	}while(exp->front != NULL);
}
