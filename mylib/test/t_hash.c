#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../include/myhash.h"
// edit library implement search func.
// test h_search - call on same keys and verify that is same result as the initial call to insert

static void dumpTable (HashTable *table) {
	// Scope - take a hashTable and iterate through each array element with each
	// element containing pointers to has nodes; in essence containing a linked list

	// First eleemnt in array of pointers will be the first node
	// HashNode **hNodePtr == &hNodePtr[i]
	HashNode **hNodePtr = table->h_items;
	// The last element of the array of pointer will be the size defined in the
	HashNode **hNodePtrZ = hNodePtr+ table->h_size;
	// A new nash node - can be null or something else
	HashNode *node;

	fputs("HASHTABLE DUMP \n",stderr);
	do {
		// Derefenrce one level and set it to node
		node = *hNodePtr;
		// Check first if node is not null - don't print info
			while (node != NULL) {
				fprintf(stderr, "De-ref the pointer at %p we have our nosde linked list with values:\n\
					h_next:  Address: %p\n\
					h_key:   Address: %p, Value: %s\n\
					h_value: Address: %p, Value: %s\n",
					(void *)node,
					(void *)node->h_next,
					(void *)node->h_key,
					(void *)node->h_key,
					(void *)node->h_value,
					(void *)node->h_value
					);
			// Should the linked list inside each *node contain extra elements
			// in the case of a collision the we move to the next element in that list
			// Otherwise if that next pointer is null then we printed our only value
			node = node->h_next;
		}
	// Increase by one element inside the array (move by one array bucket )
	} while (++hNodePtr < hNodePtrZ);
}


// insert multpile keys
//


int main(int argc, char** argv){
	HashTable *tableResult = h_create(10);
	assert(tableResult != NULL);
	FILE *stream;
	// The pointer to the line which was read
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	
	if (argc != 2) {
		fprintf(stderr,"Usage: %s <filename>\n", argv[0]);
	} else {
		if ( (stream = fopen(argv[1], "r") ) == NULL) {
			perror("Open failed");
			exit(1);
		} else {
			
		
	HashNode  *nodeResult = h_insert(tableResult, "400", "101");
	assert(nodeResult != NULL);

	HashNode  *nodeResult2 = h_insert(tableResult, "401", "102");
	HashNode  *nodeResult3 = h_insert(tableResult, "400", "1034444444444444");
	dumpTable(tableResult);
	printf("________________\n");
	HashNode *searchResult = h_search(tableResult,"400");
	h_delete(tableResult,"400");
	dumpTable(tableResult);

	return 0;
}
