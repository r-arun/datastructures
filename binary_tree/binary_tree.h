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
	int pos;
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

node * create_node(bin_tree * value,int pos){
	node * ret = (node *)malloc(sizeof(node));
	if(!ret) return NULL;
	ret->data = value;
	ret->next = NULL;
	ret->pos = pos;
	return ret;
}

void enqueue(struct queue * q, bin_tree * value, int pos){
	if(!q) return;
	node * ret = create_node(value, pos);
	if(!ret) return;
	if(!q->rear){
		q->rear = q->front = ret;
	}
	else{
		q->rear->next = ret;
		q->rear = ret;
	}
}

node * dequeue(struct queue * q){
	assert(q && q->front);
	node * val = create_node(q->front->data, q->front->pos); 
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
	enqueue(q, root, 0);
	if(!root)
		return;
	test_tree_queue(q, root->left);
	test_tree_queue(q, root->right);
}

void print_space(int space){
if(space > 0)
	while(space--)
		printf(" ");
}

static int _height(bin_tree * root){
	if(!root) return 0;
	int left_height = _height(root->left);
	int right_height = _height(root->right);
	return left_height > right_height? left_height: right_height + 1;
}

void visualize(bin_tree *root){
	if(!root){
		puts("Empty Tree");
	}
	struct queue * exp = init_queue();	
	struct queue * vis = init_queue();	
	enqueue(exp, root, 0);
	int h= _height(root);
	do{
		assert(exp->rear != NULL);
		struct queue * t = exp;
		exp = vis;
		vis = t;
		print_space(1<<(h));
		//swap(&vis, &exp);
		int pos = 0;
		while(vis->front != NULL){
			node * nd = dequeue(vis);
			if(nd && nd->data){
					//printf("Printing: %d, %d", pos, nd->pos);
				while(pos < nd->pos){
					print_space(1<<(h+1));
					pos++;
				}
				bin_tree * _node = nd->data;
				printf("%2d", _node->data);
				print_space(1<<(h+1));
				enqueue(exp, _node->left, nd->pos * 2 );
				enqueue(exp, _node->right, nd->pos * 2 + 1);
			}
			else if(nd){
					//printf("Printing: %d, %d", pos, nd->pos);
				while(pos < nd->pos){
					print_space(1<<(h+1));
					printf(" ");
					pos++;
				}
				printf("X");
				print_space(1<<(h+1));
			}
				pos++;
		}
		printf("\n");
		assert(vis->rear == NULL);
		h--;
	}while(exp->front != NULL);
}
