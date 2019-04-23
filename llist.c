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

void readfile( FILE *fptr, char *fn ) {
	char data[1000];
	
	
	while(fgets (data,sizeof(data),fptr) != NULL) {
		saveline(data);
	}

}		
int main(int argc, char** argv){

	int rc = 0;

	FILE* fptr;
	char* fname;
	char* text = argv[1];

	if(argc > 2){
		fprintf(stderr,"Filename provided is: %s\n", argv[2]);
		rc = 0;
	} else if (argc == 1){
		fprintf(stderr, "Reading from stdin\n"  );
		rc = 0;
	} else {
		fprintf(stderr,"Usage: %s text [file ...]\n", argv[0]);
		rc = 0;
	}
	return rc;
}
//- main function
//- write list - for statement to loop the linked list
//- in each iteration write text memeber to stdout
//- program can be called with 0 or 1 argument
//- no argument from stdin or 1 arg from file to read.