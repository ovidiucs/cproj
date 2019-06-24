#include <stddef.h>
#include <stdio.h>
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

	HashNode  *nodeResult = h_insert(tableResult, "400", "101");
	assert(nodeResult != NULL);

	HashNode  *nodeResult2 = h_insert(tableResult, "401", "102");

	HashNode  *nodeResult3 = h_insert(tableResult, "400", "1034444444444444");

	HashNode *searchResult = h_search(tableResult,"400");

	dumpTable(tableResult);
#if 0
	int i = 0;


	char *strings[2];
	strings[0] = "aac";
	strings[1] = "ccc";
	strings[2] = "ddd";`
	char *sndstring[2];
	sndstring[0] = "fff";
	sndstring[1] = "ggg";
	sndstring[2] = "hhh";

	do {
		// Otherwise add to the the index returnded by the hasing function
		// Will print
	fprintf(stderr,"Struct HashTable address: %p, HashNode** : %p, HashNode* : %p, hash->h_items[%d]: %p\n\n",
					h_result,
					h_result->h_items,
					h_result->h_items[resultHash],
					resultHash,
					h_result->h_items[resultHash]
					);
	fprintf(stderr,"Struct HashNode address: %p, HashNode value: %s, HashNode key: %s, HashNode next: %p\n",
					h_Nresult,
					h_Nresult->h_value,
					h_Nresult->h_key,
					h_Nresult->h_next
					);
		// Set i to...
		i +=1;
		// While condition is bad
	} while (h_result->h_items[i]  != NULL);

#endif
	return 0;
}
