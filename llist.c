#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>

typedef struct Node {

	// store pointer address of next block of data - 8 bytes / 64 bit - 4 bytes / 32 bit arch
	struct Node *next;

	// dynamically resied for malloc uses
	char text[1];

} Node;

static Node* head;
// Node* tail;

static void saveline(char *data) {

	// initialize return value, a temporary Node and a previous node
	int ret = 0;
	Node* tempNode;
	Node* prevNode;

	// Inital node
	Node* nodePointer;

	// Allocate memory - malloc returns a generic pointer.
	// We then cast Node* such that malloc has a base type of Node instead of generic void*.
	nodePointer = (Node*) malloc (sizeof(Node) + strlen(data));

	// set nodePointer->next member to NULL
	nodePointer->next = NULL;

	// Copy bytes to struct memeber 'text'
	strcpy(nodePointer->text,data);

	// Insert node in list in the right place in sorted order

	// 1. If head Node is NULL then set head to nodePointer;  - save nodePointer address
	if (head == NULL) {
		head = nodePointer;
	// 2. Otherwise - head already is set. Now set previous Node to NULL to keep track of
	// previously traversed nodes. - temp variable.
	} else {
	prevNode = NULL;
	// 3. assign head to temp node and while it's not null then assign the
	// address of the next element in the list to temp node.
		for (tempNode=head; tempNode!=NULL ; tempNode=tempNode->next){
	// 4. compare string pointed to by nodePointer and tempNode
			ret = strcmp(nodePointer->text, tempNode->text);
	// 5. if the comparsion returns less than or equal to 0
			if (ret <= 0) {
	// 5a. if the previous node is NULL
				if (prevNode == NULL) {
	// 5b. then set head to nodePointer
					head = nodePointer;
				} else {
	// 5c. otherwise set the prevNode->next to nodePointer
					prevNode->next = nodePointer;
				}
				// end if prevNode == NULL
	// 6.
				  nodePointer->next=tempNode;
				return;
			}
			// end if ret <= 0
			prevNode = tempNode;
		 }
		 // end for loop
	prevNode->next = nodePointer;
	}
	// emd else
}

static int  readfile( FILE *fptr, char *fname ) {
	char data[1000];
	int rc = 0;

	while(fgets (data,(int)sizeof(data),fptr) != NULL) {
		saveline(data);
	}
	return rc;
}
int main(int argc, char** argv){

	int rc = 0;
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
			rc = readfile(fptr, fname);
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

	Node* prevNode;

	for (;;) {
		fprintf(stderr,"Node#: %d, at mem. address: %p with sizeof line: %d data is: %s",
						numNode, (void *) tempNode, (int)strlen(tempNode->text),tempNode->text);
		numNode += 1;
		prevNode = tempNode->next;
		free((void *) tempNode);
		if (prevNode == NULL) {
			break;
		} else {
			tempNode = prevNode;
		}
	}
		return rc;

}

