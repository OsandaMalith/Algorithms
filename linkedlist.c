#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

struct node *list = NULL;
struct node *makenode(int );
int add(struct node **, int ) ;
struct node* find(struct node* ,int );
void display(struct node* list);
struct node* previous(struct node* , struct node* );
int removenode(struct node** , int );
void Insert();
void Search();
void Remove();

int
main () {
	int input;
	printf("\n\n[~] Linked List Purely written by Osanda Malith Jayathissa\n");
	printf("I am not trying to re-invent the wheel, just for fun wrote this :)\n");
	while(1) {
	printf("\n\n1. Insert into the List\n2. Search the List\n3. Remove node \ 
	\n4. Exit\n>> ");
	scanf("%i", &input);
	switch(input) {
		case 1:Insert();break;
		case 2:Search();break;
		case 3:Remove();break;
		case 4:return 0;
	} }
}

struct node *makenode(int item) {
	struct node *temp = (struct node *) malloc(sizeof(struct node));
	if(temp) temp->data = item;
	return temp;
}

int add(struct node **list, int item) {
	struct node *temp = makenode(item);
	if(!temp) return 0;
	temp->next = *list;
	*list = temp;
	return 1;
}

struct node* find(struct node* list,int item){
	for(; list; list=list->next) if(list->data == item) return list;
	return 0;
}

void display(struct node* list) {
	int i; for(; list; list = list->next) printf("\t%i", list->data);
}

struct node* previous(struct node* list, struct node* ptr) {
    for(; list; list=list->next) if(list->next==ptr) return list;
    return 0;
}

int removenode(struct node** list, int item) {
	struct node *ptr;
	struct node *temp = find(*list, item);
	if(!temp) return 0;
	ptr = previous(*list, temp);
	if(ptr) ptr->next=temp->next;
	else *list=temp->next;
	free(temp);
	return 1;
}

void Insert() {
	
	int i, n, x; 
	printf("How many nodes? "); scanf("%i", &n);
	for (i = 0; i < n; ++i) { printf("\nEnter your number: "); scanf("%d", &x); 
		add(&list, x); display(list); }
}

void Search() {
	int n;
	struct node *p;
	printf("Enter your value: "); scanf("%i", &n);
	if(p = find(list, n)) printf("\nFound the value: %i", p->data);
	//printf("\n\nFound the value: %i", ((p = find(list, n)) ? p->data : -1));
	else printf("Value not Found");
}

void Remove() {
	int n; printf("Enter your value to be removed: "); scanf("%i", &n);
	if(removenode(&list, n)) printf("\nItem is removed\n"); else printf("Value not found");
	display(list);
}
