#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

typedef struct Node {
	// store pointer address of next block of data - 8 bytes / 64 bit - 4 bytes / 32 bit arch
	struct Node *next;
	// dynamically resied for malloc uses
	char text[1];
} Node;

Node* head = NULL;
Node* tail = NULL;

void saveline(char *data) {

	// fprintf(stderr,"Entered saveline linked list.\n");

	// Allocate a new node
	Node* nodePointer;

	// Allocate memory - malloc return generic pointer -> cast Node* to malloc instead of generic one
	nodePointer = (Node*) malloc (sizeof(Node) + strlen(data));
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

int  readfile( FILE *fptr, char *fn ) {
	char data[1000];
	int rc = 0;

	while(fgets (data,sizeof(data),fptr) != NULL) {
		fprintf(stderr,"Data is: %s", data);
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
			readfile(fptr, fname);
		}
		fclose (fptr);
	} else if (argc == 1){
		fprintf(stderr, "Reading from stdin\n"  );
		rc = readfile(stdin, NULL);
	} else {
		fprintf(stderr,"Usage: %s text [file ...]\n", argv[0]);
		rc = 0;
	}

	for (tempNode=head; tempNode!=NULL ; tempNode=tempNode->next  ){
		fprintf(stderr,"Node#: %d, at mem. address: %p with sizeof line: %ld\n and data: %s",
						numNode, (void *) tempNode, strlen(tempNode->text),tempNode->text);
		numNode +=1;
	}
	return rc;
}

