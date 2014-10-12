#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "bst.h"
#define MAX(a,b) (((a)>(b))?(a):(b))
struct stack s;
//                     .-.        _              ___           _
//                      \ \      | )              |           |_)
//                       \ \     |< o._  _.._     | ._ _  _   |  ._ _  _.._ _..___
//                       | |     |_)|| |(_|| \/   | | (/_(/_  |  | (_)(_)| (_|| | |
//                       | |                 /                         _)
//     /\---/\   _,---._ | |     Name: Binary Tree Program
//    /^   ^  \,'       `. ;      Copyright: Osanda Malith Jayathissa
//   ( O   O   )           ;      Author: Osanda Malith Jayathissa
//    `.=o=__,'            \      Date: 15/08/14 20:24
//      /         _,--.__   \     Description: This application can create binary
//     /  _ )   ,'   `-. `-. \   search trees, arbitrary trees, left and right only
//    / ,' /  ,'        \ \ \ \  trees and
//   / /  / ,'          (,_)(,_)  can manipulate based on the users input
//  (,;  (,,)

clock_t tic;
clock_t toc;

void bst() {
	int v,i,j; printf("Enter how many nodes: "); scanf("%i", &j);
	for (i=0; i < j; i++)  {
		printf("Enter your values: "); scanf("%i", &v); tic = clock();
		addnode(&tree, v) ;
		toc = clock();printf("\nFunction completed in %f seconds.", (double)(toc - tic) / CLOCKS_PER_SEC);
		printf("New Node Added\n");
	} push(&s,1);  getch();
}

void leftonly() {
	printf("Enter how many nodes: ");
	int i,j,v; scanf("%i", &j);
	for (i=0; i < j; i++)  {
		printf("Enter your values: "); scanf("%i", &v); tic = clock();
		addnodeLeft(&tree, v) ;
		toc = clock();printf("\nFunction completed in %f seconds.", (double)(toc - tic) / CLOCKS_PER_SEC);
		printf("New Node Added\n");
	} push(&s,2);getch();
}

void rightonly() {
	printf("Enter how many nodes: ");
	int i,j,v; scanf("%i", &j);
	for (i=0; i < j; i++)  {
		printf("Enter your values: "); scanf("%i", &v); tic = clock();
		addnodeRight(&tree, v) ;
		toc = clock();printf("\nFunction completed in %f seconds.", (double)(toc - tic) / CLOCKS_PER_SEC);
		printf("New Node Added\n");
	} push(&s,3);getch();
}

void binarySearch() {
	int n; printf("\nEnter an value to be searched: "); scanf("%i",&n);
	if(isBst(tree)) {if(search(tree, n)) printf("value found: %i\n", search(tree, n)->data);
	else printf("Value not found\n");}
	else {SearchAB(tree, n);tic = clock(); printf("value found: %i\n", SearchAB(tree, n)->data);toc = clock();printf("\nFunction completed in %f seconds.", (double)(toc - tic) / CLOCKS_PER_SEC);}
	getch();
}

void display() {
	int n; printf("1. InOrder\n2. PreOrder\n3. PostOrder\n4. Level Order\n"); scanf("%i",&n);
	switch(n) {
	case 1:tic = clock();inorder(tree); toc = clock();printf("\nFunction completed in %f seconds.", (double)(toc - tic) / CLOCKS_PER_SEC); getch(); break;
	case 2:tic = clock();preorder(tree);toc = clock();printf("\nFunction completed in %f seconds.", (double)(toc - tic) / CLOCKS_PER_SEC); getch(); break;
	case 3:tic = clock();postorder(tree);toc = clock();printf("\nFunction completed in %f seconds.", (double)(toc - tic) / CLOCKS_PER_SEC); getch(); break;
	case 4:tic = clock();print(tree);toc = clock();printf("\nFunction completed in %f seconds.", (double)(toc - tic) / CLOCKS_PER_SEC); getch(); getch(); break;

	}
}

void AbBintree() {
	int *A = (int *) malloc(8*sizeof(int)), i;
	printf("Enter 8 values: ");
	for(i=0;i<8;i++) scanf("%i",&A[i]);tic = clock();
	//for(i=0;i<8;i++) printf("%d\t",A[i]);
	tree=makenode(A[0]);
	tree->left=makenode(A[1]);
	tree->right=makenode(A[2]);
	tree->left->left=makenode(A[3]);
	tree->left->right=makenode(A[4]);
	tree->left->right->right=makenode(A[5]);
	tree->left->left->left=makenode(A[6]);
	toc = clock();printf("\nFunction completed in %f seconds.", (double)(toc - tic) / CLOCKS_PER_SEC);
	getch();
}

void deleteNode(){
	int n;
	if(isBst(tree)) { printf("Enter value to delete: "); scanf("%i",&n);
	if(search(tree, n)) { delete(tree,n); printf("Deleted"); } else printf("Value not found"); } getch();
}

void Min() {
	tic = clock();
	struct treenode *temp_bst = (struct treenode *) malloc(sizeof(struct treenode));
	temp_bst->data = temp_bst->right = temp_bst->left = NULL;
	if(!isBst(tree)) { binary_to_bst_temp(tree, temp_bst);
	printf("Min is %i\n", findMin(temp_bst)->data); }
	else if(findMin(tree)) printf("Min is %i\n", findMin(tree)->data); else printf("Error Tree is empty\n");
	toc = clock();printf("\nFunction completed in %f seconds.", (double)(toc - tic) / CLOCKS_PER_SEC);
	getch();
}

void Max() {
	tic = clock();
	struct treenode *temp_bst = (struct treenode *) malloc(sizeof(struct treenode));
	temp_bst->data = temp_bst->right = temp_bst->left = NULL;
	if(!isBst(tree)) {  binary_to_bst_temp(tree, temp_bst);
	printf("Max is %i\n", findMax(temp_bst)->data); }
	else if(findMax(tree)) printf("Max is %i\n", findMax(tree)->data); else printf("Error Tree is empty\n");
	toc = clock();printf("\nFunction completed in %f seconds.", (double)(toc - tic) / CLOCKS_PER_SEC);
	getch();
}

void ConvBST(){
	struct treenode *temp_bst=0;
	if(!pop(&s)) {  binary_to_bst(tree);
	printf("\nConverted\n");push(&s,1);}
	else printf("Your tree is a Binary tree");
	getch();
}

void BalanceTree() {
	print_to_array(tree);
	sort_arr();
	tree = convert_to_bst(0, sort_array_count - 2);
}

void Sort() {
	tic = clock();
	print_to_array(tree);
	sort_arr();
	for(i = 0; i < sort_array_count; i++) printf("Sorted order: %d\t", sort_array[i]);
	printf("\nFunction completed in %f seconds.", (double)(toc - tic) / CLOCKS_PER_SEC);
	getch();
}

void MaxHeap() {
	tic = clock();
	print_to_array(tree);
	sort_arr();
	destroy(&tree);
	tree = NULL;
	for(i = sort_array_count - 1; i >= 0 ; i--) addnode(&tree, sort_array[i]);
	toc = clock();
	printf("\nTree converted to a Max-Heap.");
	printf("\nFunction completed in %f seconds.", (double)(toc - tic) / CLOCKS_PER_SEC);
	getch();
}

void MinHeap() {
	tic = clock();
	print_to_array(tree);
	sort_arr();
	destroy(&tree);
	tree = NULL;
	for(i = 0; i < sort_array_count; i++) insert(&tree, sort_array[i]);
	toc = clock();
	printf("\nTree converted to a Min-Heap.");
	printf("\nFunction completed in %f seconds.", (double)(toc - tic) / CLOCKS_PER_SEC);
	getch();
}

void max_min_leaf() {
	tic = clock();
	find_max_min_leaf_nodes(tree);
	toc = clock();
	min_leaf_node = (min_leaf_node == 0) ? max_leaf_node : min_leaf_node;
	printf("\nThe minimum leaf node level: %d", min_leaf_node - 1);
	printf("\nThe maximum leaf node level: %d", max_leaf_node - 1);
	printf("\nConsidering the root of the tree as level 0");
	printf("\n\nFunction completed in %f seconds.", (double)(toc - tic) / CLOCKS_PER_SEC);
	getch();
}
void insert_menu() {
	int op;
	printf("\n1. Binary Search tree\n2. Arbitrary Binary Tree\n3. Left only tree\n4. Right Only tree\n\n>> ");
	scanf("%i", &op); fflush(stdin);
	switch(op) {
		case 1: destroy(&tree); bst();break;
		case 2: destroy(&tree); AbBintree();break;
		case 3: destroy(&tree); leftonly();break;
		case 4: destroy(&tree); rightonly();break;
		default:printf("Enter a valid choice"); getch(); break;
	}
}
int
main () {
	int option,n;
	struct treenode *value;

	while(1) {
		system("cls & title Binary Tree & color 17"); fflush(stdout); if(full(&s)) while (!empty(&s)) pop(&s);
		printf("\t       _ )_)                    __ __|\n");
		printf("\t       _ \\ |   \\   _` |  _||  |    |  _|-_)  -_)(_-<\n");
		printf("\t      ___/_|_| _|\\__,_|_| \\_, |   _|_|\\___|\\___|___/\n");
		printf("\t                          ___/ \n");
		printf("\t\t\t  Author: Osanda Malith Jayathissa\n\t\t\t  CB:\t  CB005094\n\n");
		printf("1. Insert into a tree\n");
		printf("2. Display\n3. Find Min\n");
		printf("4. Find Max\n5. Search the tree\n");
		printf("6. Find the number of nodes\n");
		printf("7. Sort the tree\n");
		printf("8. Convert a arbitrary binary tree to a BST\n");
		printf("9. Destroy a tree\n");
		printf("10. Check BST or not\n");
		printf("11. Delete a node\n");
		printf("12. Convert to a Max heap\n");
		printf("13. Convert to a Min Heap\n14. Find height\n");
		printf("15. Balance a Tree\n");
		printf("16. Find the Max and Min of the leaf nodes\n17. Exit\n\n>> ");
		scanf("%i", &option); fflush(stdin);
		switch(option) {
			case 1:insert_menu(); break;
			case 2:display(); break;
			case 3:Min();break;
			case 4:Max(); break;
			case 5:binarySearch(); break;
			case 6:printf("You trees has %d nodes", count(tree)); getch(); break;
			case 7: Sort();break;
			case 8:ConvBST(); break;
			case 9:destroy(&tree); break;
			case 10:tic = clock();if(isBst(tree)) printf("\nThis is a Binary Search Tree\n"); else printf("\nThis is not a Binary Search Tree\n");toc = clock();printf("\nFunction completed in %f seconds.", (double)(toc - tic) / CLOCKS_PER_SEC); getch(); break;
			case 11:deleteNode(); break;
			case 12:MaxHeap();break;
			case 13:MinHeap(); break;
			case 14:tic = clock();printf("Height: %i \n",MAX(findHeight(tree->left),findHeight(tree->right))); toc = clock();printf("\nFunction completed in %f seconds.", (double)(toc - tic) / CLOCKS_PER_SEC);getch(); break;
			case 15:BalanceTree();getch();break;
			case 16:max_min_leaf(); break;
			case 17:exit(0);
			default:printf("Enter a valid choice"); getch(); break;
		}
	}
	getch();
}
/*EOF*/
