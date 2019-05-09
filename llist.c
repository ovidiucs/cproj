#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>

// A binary tree is composed of
// root node;
// -- parent
// -- nodes,
// -- or leaves,

typedef struct bstNode {
	struct bstNode *bleft;
	struct bstNode *bright;
	char *bstext;

} bstNode;

typedef struct Node {

	// store pointer address of next block of data - 8 bytes / 64 bit - 4 bytes / 32 bit arch
	struct Node *next;

	// dynamically resied for malloc uses
	char text[1];

} Node;

static Node* head;
static Node* tail;
// Inital node - root
static bstNode *root;

static void saveline(char *data) {

	// initialize return value, a temporary Node and a previous node
	int ret = 0;
	int counter = 0;
	Node* tempNode;
	Node* prevNode;
	// Inital node
	Node* nodePointer;

	// Allocate memory - malloc returns a generic pointer.
	nodePointer = (Node*) malloc (sizeof(Node) + strlen(data));

	// set nodePointer->next member to NULL
	nodePointer->next = NULL;


	// Copy bytes to struct memeber 'text'
	strcpy(nodePointer->text,data);
	if (head == NULL) {
		head = tail = nodePointer;
	} else {
		tail->next = nodePointer;
		tail = nodePointer;
	}
}

//static insertNode(bstNode* root, char *data){
//
//}

static void bstSaveLine(char *data) {

	root = NULL;
	int result = 0;

	// Allocate memory - malloc returns a generic pointer.
	root = (bstNode*) malloc (sizeof(bstNode));
	root->bstext = (char*) malloc(sizeof(data));
		fprintf(stderr,"Malloc for root is: %p, sizeof root node is %d\n", root,(sizeof(bstNode)));
   	fprintf(stderr,"Malloc for char* is: %p, sizeof char*  is %d\n", root->bstext,(sizeof(data)));

	// set nodePointer->next member to NULL
	root->bleft = NULL;
	root->bright = NULL;


	// Copy bytes to struct memeber 'text'
	result = strcmp(data,root->bstext);

	fprintf(stderr,"Result is: %d - String is: %s Data is: %s\n", result,root->bstext, data);

	if (result == 0) {
		// root = root;
		fprintf(stderr,"Result == %d ' ' %s\n", result,root->bstext);
	} else if (result < 0 ) {
				fprintf(stderr,"Result < 0 so: %d ' ' %s\n", result,root->bstext);
		// return root->bleft;
	} else {
		fprintf(stderr,"Result > %d ' ' %s\n", result,root->bstext);
		// return root->bright;
	}

}

static int readfile( FILE *fptr, char *fname ) {

	char data[1000];
	int counter = 0;

	while(fgets (data,(int)sizeof(data),fptr) != NULL) {
		//saveline(data);
		bstSaveLine(data);
		counter +=1;
	}
	return counter;
}

static int compar (const void *a,  const void *b) {
		//https://cboard.cprogramming.com/c-programming/64520-sorting-linked-list-qsort.html#post458752

    int i = strcmp( (**( const Node**)a).text, (*( const Node**)b)->text );
    fprintf(stderr,"%d and string A %p and string B %p\n", i,a,b);
    return i;
}
	// Function main executes the main body of the program. Arguments: argc and argv. Function  main executes the main body of the program.  Arguments: argc and argv.  Function main
	 // executes the main body of the program.  Arguments: argc and argv.
int main(int argc, char** argv){

	int rc = 0;
	int counter = 0;
	FILE* fptr;
	char* fname;
	int numNode = 0;
	Node* tempNode;

	if(argc == 2){
		fprintf(stderr,"Filename provided is: %s\n", argv[1]);
		fname = argv[1];
		fptr = fopen(fname,"r");
		if (fptr == NULL) {
			fprintf(stderr,"Unable to open %s\n", fname);
			rc = 1;
		} else {
			counter = readfile(fptr, fname);
		}
		rc = fclose (fptr);
	} else if (argc == 1){
		fprintf(stderr, "Reading from stdin\n");
		rc = readfile(stdin, NULL);
	} else {
		fprintf(stderr,"Usage: %s text [file ...]\n", argv[0]);
		rc = 0;
	}
/*
	tempNode=head;
	Node* arrayNode[counter];
	Node* prevNode;

	for (tempNode=head;tempNode!=NULL;tempNode=tempNode->next) {
		fprintf(stderr,"Node#: %d, allocated mem. address: %p with strlen of text: %d data is: %s",
						numNode, (Node *) tempNode, (int)strlen(tempNode->text),tempNode->text);
		arrayNode[numNode] = tempNode;

		numNode += 1;
	}
		int i = 0;
		qsort ( (void *) arrayNode,
		(size_t) counter,
		sizeof(Node *),
		compar);

		for (i=0;i<counter;i++) {
		fprintf(stderr,"Array element: %d memory address of text %p with string %s",
							i, arrayNode[i]->text,arrayNode[i]->text);
	}
//		for (i=0;i<10;i++) {
//		fprintf(stderr,"\tArray loop: %d memory address of text %p with string (char *) %s\n",i, arrayNode[i]->text,arrayNode[i]->text);
//	}
*/
		return rc;

	}

//}

