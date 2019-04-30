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

	int ret = 0;
	Node* tempNode;
	Node* prevNode;
	// fprintf(stderr,"Entered saveline linked list.\n");

	// Allocate a new node
	Node* nodePointer;

	
	// Allocate memory - malloc return generic pointer -> cast Node* to malloc instead of generic one
	nodePointer = (Node*) malloc (sizeof(Node) + strlen(data));
	nodePointer->next = NULL;
	

	// Copy bytes to struct memeber 'text'
	strcpy(nodePointer->text,data);
	// Insert node in list in the right place in sorted order
	
	if (head == NULL) {
		head = nodePointer;
		
	} else {
		prevNode = NULL;
		for (tempNode=head; tempNode!=NULL ; tempNode=tempNode->next){
			ret = strcmp(nodePointer->text, tempNode->text);
			if (ret <= 0) {
				if (prevNode == NULL) {
					head =  nodePointer;
				} else {
					prevNode->next = nodePointer;
				}
				nodePointer->next=tempNode;
				//goto label;
				return;
			} 
			prevNode = tempNode;
		}
		prevNode->next = nodePointer;
//label:
			
	}


}

int  readfile( FILE *fptr, char *fn ) {
	char data[1000];
	int rc = 0;

	while(fgets (data,sizeof(data),fptr) != NULL) {
	//	fprintf(stderr,"Data is: %s", data);
		saveline(data);
	}
	return rc;
}
int main(int argc, char** argv){

	int rc = 0;
	int ret = 0;
	int i = 0;
	FILE* fptr;
	char* fname;
	int numNode = 0;
	Node* tempNode;
//	Node* nodeList[1000];

	//nodeList = (Node*) malloc (sizeof(Node));

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
		fprintf(stderr, "Reading from stdin\n");
		rc = readfile(stdin, NULL);
	} else {
		fprintf(stderr,"Usage: %s text [file ...]\n", argv[0]);
		rc = 0;
	}
	tempNode=head;
	Node* prevNode;
	
	for (;;) {
		fprintf(stderr,"Node#: %d, at mem. address: %p with sizeof line: %ld data is: %s",
						numNode, (void *) tempNode, strlen(tempNode->text),tempNode->text);
		prevNode = tempNode->next;
		free((void *) tempNode);
		if (prevNode == NULL) {
			break;
		} 
		tempNode = 
	}
	

/*
for (tempNode=head; tempNode!=NULL ; tempNode=tempNode->next) {
	for (tempNode=head; tempNode!=NULL ; tempNode=tempNode->next) {
		if (tempNode->next == NULL){
			break;
		} else {
			ret = strcmp(tempNode->text,(tempNode->next->text));
			fprintf(stderr,"\t Pointer of next is %p\t i is %d nad ret code is %d\n",(void *)tempNode->next,i,ret);
		}
		i+=1;
	}
}

	while (nodeList[i] != NULL){
		if (nodeList[i+1] == NULL){
			break;
		} else {
			ret = strcmp(nodeList[i]->text,nodeList[i+1]->text);
			fprintf(stderr,"\t Pointer of next is %p\t i is %d\n",nodeList[i]->next,i);
			if (ret > 0){
				nodeList[i]->next=nodeList[i-1]->next;
				fprintf(stderr,"Data is:%s \t%d, ret is > 0 pointer of next is %p\n",nodeList[i]->text,ret,nodeList[i]->next);
			} else if (ret < 0){
				fprintf(stderr,"Data is:%s \t%d, ret < 0 pointer of next is %p\n",nodeList[i]->text,ret,nodeList[i]->next);
				nodeList[i]->next=nodeList[i+1]->next;
			} else {
				fprintf(stderr,"\t%d, ret is 0 => Equal\n", ret);
			}
		}
		i+=1;
	}
*/
		return rc;

}

