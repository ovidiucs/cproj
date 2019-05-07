#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>


typedef struct bst {
	struct bst *bleft;
	struct bst *bright;
	char *btext;

} bst;

typedef struct Node {

	// store pointer address of next block of data - 8 bytes / 64 bit - 4 bytes / 32 bit arch
	struct Node *next;

	// dynamically resied for malloc uses
	char text[1];

} Node;

static Node* head;
static Node* tail;

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

static void bstSaveLine(char *data) {

	// initialize return value, a temporary Node and a previous node
	int result = 0;
	int counter = 0;

	// Inital node
	bst* rootBstPointer;

	// Allocate memory - malloc returns a generic pointer.
	rootBstPointer = (bst*) malloc (sizeof(bst));
	rootBstPointer->btext = (char*) malloc(sizeof(data));

	// set nodePointer->next member to NULL
	rootBstPointer->bleft = NULL;
	rootBstPointer->bright = NULL;


	// Copy bytes to struct memeber 'text'
	result = strcmp(rootBstPointer->data);


	if (result == 0) {
		 rootBstPointer = rootBstPointer;
	} else if (result < 0 ) {
		return rootBstPointer->bleft;
	} else {
		return rootBstPointer->bright;
	}

}

static int readfile( FILE *fptr, char *fname ) {

	char data[1000];
	int counter = 0;

	while(fgets (data,(int)sizeof(data),fptr) != NULL) {
		saveline(data);
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
		fprintf(stderr,"\nArray element: %d memory address of text %p with string %s sizeof %ld",
							i, arrayNode[i]->text,arrayNode[i]->text, sizeof(Node*));
	}
//		for (i=0;i<10;i++) {
//		fprintf(stderr,"\tArray loop: %d memory address of text %p with string (char *) %s\n",i, arrayNode[i]->text,arrayNode[i]->text);
//	}
		return rc;

	}

//}

