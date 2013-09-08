#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

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

static int _count(bin_tree * root){
	if(!root) return 0;
	return _count(root->left)+_count(root->right)+1;
}

static bin_tree * insert(int * pre_order, int * in_order, int start, int limit, 
int root_pos, int size){
	bin_tree * root = NULL;
	if(start >= limit) return NULL;
	root = create_bin_tree_node(pre_order[root_pos]);
	int left_pos = start;
	for(; left_pos < limit; ++left_pos){
		if(in_order[left_pos] == pre_order[root_pos]){
			break;
		}
	}
	assert(left_pos < limit);
	root->left = insert(pre_order, in_order,  start, left_pos, root_pos+1,size);
	int cnt = _count(root->left);
	root_pos = root_pos + cnt + 1;
	if(root_pos < size)
		root->right = insert(pre_order, in_order, left_pos+1, limit, root_pos, size);
	return root;
}


void preorder(bin_tree *root){
	if(root){
		printf("%d ",root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(bin_tree *root){
	if(root){
		inorder(root->left);
		printf("%d ",root->data);
		inorder(root->right);
	}
}

void postorder(bin_tree *root){
	if(root){
		postorder(root->left);
		postorder(root->right);
		printf("%d ",root->data);
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

//TODO random binary trees
static int random_in_range (unsigned int min, unsigned int max) {
	if(min == max) return min;
	int base_random = rand(); /* in [0, RAND_MAX] */
	if (RAND_MAX == base_random) return random_in_range(min, max);
	/* now guaranteed to be in [0, RAND_MAX) */
	int range       = max - min,
		remainder   = RAND_MAX % range,
		bucket      = RAND_MAX / range;
	/* There are range buckets, plus one smaller interval
	   within remainder of RAND_MAX */
	if (base_random < RAND_MAX - remainder) {
		return min + base_random/bucket;
	} else {
		return random_in_range (min, max);
	}
}

static int random_int(){
	return rand() % 100;
}

static int random_array(int * pre_order, int * in_order, int * mapping, int start,
						int limit, int size){
	if(start >= limit) return size;
	int root_pos = random_in_range(start, limit);	
	in_order[root_pos] = pre_order[size] = random_int();
	mapping[size] = root_pos;
	printf("Put at position at %d %d\n", root_pos, in_order[root_pos]);
	size = random_array(pre_order, in_order, mapping, start, root_pos, size+1);
	return random_array(pre_order, in_order, mapping, root_pos + 1, limit, size);
}

static bin_tree * insert_random_node(int * pre_order, int * in_order, int * mapping, 
							int start, int limit,int root_pos, int size){
	bin_tree * root = NULL;
	if(start >= limit) return NULL;
	root = create_bin_tree_node(pre_order[root_pos]);
	int left_pos = mapping[root_pos];
	assert(left_pos < size);
	root->left = insert_random_node(pre_order, in_order, mapping, start, left_pos, 
								root_pos+1,size);
	int cnt = _count(root->left);
	root_pos = root_pos + cnt + 1;
	if(root_pos < size)
		root->right = insert_random_node(pre_order, in_order, mapping, left_pos+1,
						limit, root_pos, size);
	return root;
}

bin_tree * create_random_binary_tree(int size){
	srand(time(NULL));
	if(size <= 0) return NULL;
	int * pre_order = (int *)malloc(sizeof(bin_tree) *size);
	int * in_order = (int *)malloc(sizeof(bin_tree) *size);
	int * mapping = (int *)malloc(sizeof(bin_tree) *size);
	random_array(pre_order, in_order, mapping, 0, size, 0);
	int i;
	for(i = 0; i < size; ++i){
	 printf("%d ", pre_order[i]);
	}
	puts("");
	for(i = 0; i < size; ++i){
	 printf("%d ", in_order[i]);
	}
	puts("");
	bin_tree * root = insert_random_node(pre_order, in_order, mapping, 0, size, 0,
												size);
	free(pre_order);
	free(in_order);
	free(mapping);
	return root;
}

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

static node * create_node(bin_tree * value,int pos){
	node * ret = (node *)malloc(sizeof(node));
	if(!ret) return NULL;
	ret->data = value;
	ret->next = NULL;
	ret->pos = pos;
	return ret;
}

static void enqueue(struct queue * q, bin_tree * value, int pos){
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

static node * dequeue(struct queue * q){
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

static void print_queue(struct queue * q){
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

static void print_space(int space){
if(space > 0){
	while(space--)
		printf(" ");
	}
}

static int _height(bin_tree * root){
	if(!root) return 0;
	int left_height = _height(root->left);
	int right_height = _height(root->right);
	return (left_height > right_height? left_height: right_height) + 1;
}

void pretty_print(bin_tree *root){
	if(!root){
		puts("Empty Tree");
	}
	struct queue * exp = init_queue();	
	struct queue * vis = init_queue();	
	enqueue(exp, root, 0);
	int h= _height(root);
	int spaces = 1<<h;
	//if(spaces > 32) spaces = 32;
	do{
		assert(exp->rear != NULL);
		struct queue * t = exp;
		exp = vis;
		vis = t;
		print_space(spaces);
		//swap(&vis, &exp);
		int pos = 0;
		while(vis->front != NULL){
			node * nd = dequeue(vis);
			if(nd && nd->data){
					//printf("Printing: %d, %d", pos, nd->pos);
				while(pos < nd->pos){
					print_space(spaces);
					pos++;
				}
				bin_tree * _node = nd->data;
				printf("%2d", _node->data);
				print_space(2*spaces);
				enqueue(exp, _node->left, nd->pos * 2 );
				enqueue(exp, _node->right, nd->pos * 2 + 1);
			}
			else if(nd){
					//printf("Printing: %d, %d", pos, nd->pos);
				while(pos < nd->pos){
					print_space(2 * spaces);
					printf(" ");
					pos++;
				}
				printf("X ");
				print_space(2 * spaces);
			}
				pos++;
		}
		printf("\n");
		assert(vis->rear == NULL);
		spaces/=2;
	}while(exp->front != NULL);
}
