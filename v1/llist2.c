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
static Node* tail;

static void saveline(char *data) {

	// initialize return value, a temporary Node and a previous node
	int ret = 0;
	int counter = 0;
	Node* tempNode;
	Node* prevNode;
	// -- fprintf(stderr, "Function called\n");
	// Inital node
	Node* nodePointer;

	// Allocate memory - malloc returns a generic pointer.
	// We then cast Node* such that malloc has a base type of Node instead of generic void*.
	nodePointer = (Node*) malloc (sizeof(Node) + strlen(data));
//--	fprintf(stderr, "Malloc called on nodePointer %p\n", nodePointer);

	// set nodePointer->next member to NULL
	nodePointer->next = NULL;
	//--fprintf(stderr, "Set nodePointer to %p\n", nodePointer);
	// Copy bytes to struct memeber 'text'


	// Copy bytes to struct memeber 'text'
	strcpy(nodePointer->text,data);
	if (head == NULL) {
		head = tail = nodePointer;
	} else {
		tail->next = nodePointer;
		tail = nodePointer;
	}


/*
	// Insert node in list in the right place in sorted order



	// 1. If head Node is NULL then set head to nodePointer;  - save nodePointer address
	if (head == NULL) {
		head = nodePointer;
				fprintf(stderr, "If condition head is null so set it to: %p \n",head );
	// 2. Otherwise - head already is set. Now set previous Node to NULL to keep track of
	// previously traversed nodes. - temp variable.
	} else {
	prevNode = NULL;
	// 3. assign head to temp node and while it's not null then assign the
	// address of the next element in the list to temp node.
		for (tempNode=head; tempNode!=NULL ; tempNode=tempNode->next){
		fprintf(stderr, "Head is: %p\t tempNode is: %p\t tempNode->next is: %p\n",
				head, tempNode, tempNode->next );
	// 4. compare string pointed to by nodePointer and tempNode
			ret = strcmp(nodePointer->text, tempNode->text);
	// 5. if the comparsion returns less than or equal to 0
			if (ret <= 0) {
	// 5a. if the previous node is NULL
				if (prevNode == NULL) {
	// 5b. then set head to nodePointer
						fprintf(stderr, "Head is: %p\n ", head);

					head = nodePointer;
				} else {
	// 5c. otherwise set the prevNode->next to nodePointer
					prevNode->next = nodePointer;
					fprintf(stderr, "\nInner PrevNode->next is: %p\n ", prevNode->next);
				}
				// end if prevNode == NULL
	// 6.
				  nodePointer->next=tempNode;
				  fprintf(stderr, "NodePointer->next is: %p\n ", nodePointer->next);
				return;
			}
			// end if ret <= 0
			prevNode = tempNode;
			fprintf(stderr, "	PrevNode is: %p\n ", prevNode);
		 }
		 // end for loop
	prevNode->next = nodePointer;
	fprintf(stderr, "PrevNode->next is: %p\n ", prevNode->next);
	}
	// emd else
	fprintf(stderr, "End of function\n");
	fprintf(stderr, "____________________\n");
	counter +=1;
	fprintf(stderr,"%d",counter);
*/
}

static int  readfile( FILE *fptr, char *fname ) {

	char data[1000];
	int counter = 0;

	while(fgets (data,(int)sizeof(data),fptr) != NULL) {
		saveline(data);
		counter +=1;
	}
	return counter;
}

static int compar (const void *a,  const void *b) {
		//xint ret = 0;
		//ret = ;
		//fprintf(stderr,"%p\n && %p\n\n",a,b);

		//https://cboard.cprogramming.com/c-programming/64520-sorting-linked-list-qsort.html#post458752
    return strcmp(((Node*)a)->text, ((Node*)b)->text);
		//return strcmp(a->text,a->text);
}

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
		//---fprintf(stderr,"NumNode Node#: %d is %p - \n\n",numNode,arrayNode[numNode]);

		numNode += 1;
		//prevNode = tempNode->next;
	// free((void *) tempNode);
	 	//if (prevNode == NULL) {`
	 //		break;
	 	//} else {
	 	//	tempNode = prevNode;
	 //	}
	}
			//---fprintf(stderr,"NumNode Node#: %p - , szof arrNode %ld\n\n",arrayNode[0],sizeof(arrayNode)/sizeof(arrayNode[0]) ) ;
	//		fprintf(stderr,"NumNode Node#: %p - \n\n",head);

//			qsort (arrayNode[counter]->text, (long unsigned int)numNode-1, sizeof(arrayNode)/sizeof(arrayNode[0]), cmpfunc);
		//;
/*
		for (counter=0;counter<numNode-1;counter++) {
			//fprintf(stderr,"Array Node#: %d - \n\n",counter);
		//fprintf(stderr,"Array Node#: %p - \n",arrayNode[counter]);
			if (arrayNode[counter+1] != NULL) {
		  fprintf(stderr,"CmpFunc: %d - \n",cmpfunc(arrayNode[counter]->text,arrayNode[counter+1]->text));
			qsort (arrayNode[counter]->text, 11, sizeof(arrayNode)/sizeof(arrayNode[0]), cmpfunc);

			}

		}
		*/

				int i = 0;

		for (i=0;i<10;i++) {
		fprintf(stderr,"\nArray loop: %d memory address of text %p with string (char *) %s",i, arrayNode[i]->text,arrayNode[i]->text);
					qsort ( (void *)	arrayNode,
					10,
					sizeof(arrayNode)/sizeof(arrayNode[i]),
					compar);
		// fprintf(stderr,"Array Node#: %d, at mem. address: %p data is: %s and sizeof is %d",
		//				counter, arrayNode[counter],arrayNode[counter]->text,(int)strlen(tempNode->text));

			//arrayNode[numNode] =(void *) tempNode;

		//prevNode = tempNode->next;
	// free((void *) tempNode);
	 	// if (prevNode == NULL) {
	 	// 	break;
	 	// } else {
	 	// 	tempNode = prevNode;
	 	// }
	}
		for (i=0;i<10;i++) {
		fprintf(stderr,"\tArray loop: %d memory address of text %p with string (char *) %s\n",i, arrayNode[i]->text,arrayNode[i]->text);
		// fprintf(stderr,"Array Node#: %d, at mem. address: %p data is: %s and sizeof is %d",
		//				counter, arrayNode[counter],arrayNode[counter]->text,(int)strlen(tempNode->text));

			//arrayNode[numNode] =(void *) tempNode;

		//prevNode = tempNode->next;
	// free((void *) tempNode);
	 	// if (prevNode == NULL) {
	 	// 	break;
	 	// } else {
	 	// 	tempNode = prevNode;
	 	// }
	}
		return rc;

	}
//}

