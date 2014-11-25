/*
This file is a part of Osanda's binary tree implementation.
Copyright (c) 2014
*/
struct treenode {
	int data;
	struct treenode *left, *right;
} *tree = 0;

struct stack {
	int sp;
	double data[10];
};

int data[10];
int i = 0;
int max_leaf_node = 0;
int min_leaf_node = 0;
int sort_array[100];
int sort_array_count = 0;
//################# STACK TO RETAIN FUNCTIONAILITY ###################################

void init(struct stack *s) {
	s->sp = -1;
}

int push (struct stack *s, double item) {
	s->data[++s->sp] = item;
	return 1;
}

double pop (struct stack *s) {
    return (s->data[s->sp--]);
}
int full (struct stack *s) { return s->sp == 10 -1; }

int empty (struct stack *s) { return s->sp == -1; }

//########################### ADD NEW NODE ##########################################
struct treenode* makenode(int item){
	struct treenode* temp = (struct treenode*) malloc(sizeof(struct treenode));
	if (temp) { temp->data=item;
	temp->left = temp->right = NULL; }
	return temp;
}

struct treenode *addnode(struct treenode **ptr, int item) {
	if (*ptr) if (item < (*ptr)->data) return addnode(&((*ptr)->left), item);
	else return addnode(&((*ptr)->right), item);
else return *ptr = makenode(item);
}
//######################### DISPLAY INORDER PREORDER POST ORDER #####################
void inorder(struct treenode *ptr) {
	if(ptr) {
    inorder(ptr->left);
	printf("%i\t", ptr->data);
	inorder(ptr->right);
}}

void preorder(struct treenode *ptr) {
	if(ptr) {
    printf("%i\t", ptr->data);
	preorder(ptr->left);
	preorder(ptr->right);
}}

void postorder(struct treenode *ptr) {
	if(ptr) {
	postorder(ptr->left);
	postorder(ptr->right);
	printf("%i\t", ptr->data);
}}
//########################## SEARCH FOR A BINARY SEARCH TREE #######################
struct treenode *search(struct treenode *ptr, int key) {
	if(!ptr) return NULL;
	if(ptr->data == key) return ptr;
	else if (key < ptr->data) return (ptr->left, key);
	else return search(ptr->right, key);
}
//########## SEARCH FOR ANY TREE #############################
struct treenode * SearchAB(struct treenode *ptr, int key) {
	struct treenode *p;
	if(ptr) {
		if(ptr->data == key) return ptr;
		if(p=SearchAB(ptr->left, key)) return p;
		return SearchAB(ptr->right,key);
	}
}
struct treenode *findMin(struct treenode *ptr) {
	if(!ptr){ return NULL; }
	else if(!ptr->left) return ptr;
	return findMin(ptr->left);
}

struct treenode *findMax(struct treenode *ptr) {
	if(!ptr){ return NULL; }
	else if(!ptr->right) return ptr;
	return findMax(ptr->right);
}

int max(int a,int b){ return(a>b?a:b); }

struct treenode *findHeight(struct treenode *ptr) {
	if(!ptr) return 0;
	return(max(findHeight(ptr->left),findHeight(ptr->right))+1);
}

struct treenode *addnodeLeft(struct treenode **ptr, int item) {
	if (*ptr) return addnodeLeft(&((*ptr)->left), item);
else return *ptr = makenode(item);
}

struct treenode *addnodeRight(struct treenode **ptr, int item) {
	if (*ptr) return addnodeRight(&((*ptr)->right), item);
else return *ptr = makenode(item);
}

void destroy(struct treenode** ptr){
	if(*ptr){ destroy(&((*ptr)->left)); destroy(&((*ptr)->right));
	          free(*ptr); *ptr=0;
}}

struct treenode *delete(struct treenode *root, int data) {
	if(root == NULL) return root;
	else if(data < root->data) root->left = delete(root->left, data);
	else if(data > root->data) root->right = delete(root->right, data);
	else {
		if(root->left == NULL && root->right == NULL) {
			free(root);
			root = NULL;

		} else if(root->left == NULL) {
			struct treenode *temp =  root;
			root = root->right;
			free(temp);

		} else {
			struct treenode *temp = findMin(root->right);
			root->data = temp->data;
			root->right = delete(root->right, temp->data);
		}
	}
	return root;
}

int isBstL(struct treenode *ptr, int value) {
	if(ptr == NULL) return 1;
	if(ptr->data <= value
		&& isBstL(ptr->left, value)
		&& isBstL(ptr->right, value))
	return 1;
	else return 0;
}

int isBstG(struct treenode *ptr, int value){
	if(ptr == NULL) return 1;
	if(ptr->data > value
		&& isBstG(ptr->left, value)
		&& isBstG(ptr->right, value))
	return 1;
	else return 0;
}

int isBst(struct treenode *ptr) {
	if(ptr == NULL) return 1;

	if(isBstL(ptr->left, ptr->data)
		&& isBstG(ptr->right, ptr->data)
		&& isBst(ptr->left)
		&& isBst(ptr->right))
		return 1;
	else return 0;
}

void inorder_to_array(struct treenode *n,int data[],int *ptr){
    if (n) {
        inorder_to_array(n->left,data,ptr);
        data[*ptr] = n->data;
        (*ptr)++;
        inorder_to_array(n->right,data,ptr);
    }
}

int count(struct treenode *n){
    int c = 1;
    if (!n)return 0; else { c += count(n->left); c += count(n->right); return c; }
}

int cmpfunc (const void * a, const void * b){ return *(int*)a - *(int*)b; }

void array_to_bst(int *arr, struct treenode *ptr, int *indexptr){
    if (ptr) {
        array_to_bst(arr,ptr->left, indexptr);
        ptr->data = arr[i++];
        array_to_bst(arr,ptr->right, indexptr);
    }
}

void binary_to_bst(struct treenode *root) {
    int n, i;
    if (!root) return;
    n = count(root);
    i = 0;
    inorder_to_array(root, data, &i);
    qsort(&data, n, sizeof(data[0]), cmpfunc);
    i = 0;
    array_to_bst(data, root, &i);
}

void binary_to_bst_temp(struct treenode *root,struct treenode *temp_bst) {

    int n, i;
    if (!root) return;
    n = count(root);
    i = 0;
    inorder_to_array(root, data, &i);
    qsort(&data, n, sizeof(data[0]), cmpfunc);
    i = 0;
    array_to_bst(data, temp_bst, &i);
}

//################### LEVEL ORDER #####################################
void print_level(struct treenode *n, int desired, int current){
    if (n)  {
        if (desired == current) {
            printf("  %5d", n->data);
        } else {
            print_level(n->left, desired, current + 1);
            print_level(n->right, desired, current + 1);
        }
   }
}

int height(struct treenode  *n){
    int lheight, rheight;
     if (n){
        lheight = height(n->left); rheight = height(n->right);
        if (lheight > rheight) return(lheight + 1);
        else return(rheight + 1);
    } else { return 0;
    }
}

void print(struct treenode *root) {
    int h, i;
    h = height(root);
    for(i = 0;i < h;i++) {
        printf("\nLEVEL %d  :", i);
        print_level(root, i, 0); printf("\n");
    }
}

//###################### SORT ###################
void sort_arr() {
	int c, d, position, swap;
 	for (c = 0 ;c < ( sort_array_count - 1 ) ;c++) {
    	position = c;
 		for (d = c + 1 ;d < sort_array_count ;d++) {
 			if (sort_array[position] > sort_array[d])
            	position = d;
      	}
      	if (position != c) {
      		swap = sort_array[c];
        	sort_array[c] = sort_array[position];
        	sort_array[position] = swap;
      	}
   }
}
//############### CONVERT TO AN ARRAY ###############
void print_to_array(struct treenode *tree){
	if (tree) {
		print_to_array(tree->left);
		print_to_array(tree->right);
		sort_array[sort_array_count++] = tree->data; }
}

struct treenode * convert_to_bst(int start, int end) {
	if (start > end) return NULL;
	int mid = start + (end - start) / 2;
	struct treenode * temp = (struct treenode *)malloc(sizeof(struct treenode));
	temp->data = sort_array[mid];
	temp->right = temp->left = 0;
	temp->left = convert_to_bst(start, mid-1);
	temp->right = convert_to_bst(mid+1, end);
	return temp;
}

//############## ADDNODE FROM AN ARRAY ###################
void insert(struct treenode **tree, int val) {
	struct treenode *temp = NULL;
	if(!(*tree)) {
		temp = (struct treenode *)malloc(sizeof(struct treenode));
		temp->left = temp->right = NULL;
		temp->data = val;
		*tree = temp;
		return;
	}
	if(val < (*tree)->data) {
			insert(&(*tree)->left, val);
		}
		else if(val > (*tree)->data) {
	    	insert(&(*tree)->right, val);
		}
}

void find_max_min_leaf_nodes(struct treenode  * tree) {
	if (tree) {
		if(tree->left == NULL && tree->right == NULL) min_leaf_node = max_leaf_node;
		find_max_min_leaf_nodes(tree->left);
		find_max_min_leaf_nodes(tree->right);
		max_leaf_node++;
	}
}
/*EOF*/
