#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

typedef struct Node {
	struct Node *next;
	char text[1];
} Node;

Node* head = NULL; 
Node* tail = NULL;

void saveline(char *data) {
	
	// fprintf(stderr,"Entered saveline linked list.\n");
	
	// Allocate a new node
	Node* nodePointer;

	// Allocate memory 
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
		fprintf(stderr,"Data is:%s", data);
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
		fprintf(stderr,"%d:%p:%s\n",numNode, (void *) tempNode, tempNode->text);
	}
	return rc;
}
//- main function
//- write list - for statement to loop the linked list
//- in each iteration write text memeber to stdout
//- program can be called with 0 or 1 argument
//- no argument from stdin or 1 arg from file to read.