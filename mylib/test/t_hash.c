#include <stddef.h>
#include <assert.h>
#include "../include/myhash.h"

// edit library implement search func.
// test h_search - call on same keys and verify that is same result as the initial call to insert

static void dumpTable (HashTable *table) {
	HashNode **hNodePtr = table->h_items;
	HashNode **hNodePtrZ = hNodePtr+table->h_size;
	HashNode *node;	
	do {
		node = *hNodePtr;
			while (node != NULL) {

	fprintf(stderr, "De-referencing the pointer at %p we have our nosde strcutre that holds:\n\
			h_next:  Address: %p\n\
			h_key:   Address: %p, Value: %s\n\
			h_value: Address: %p, Value: %s\n", hTable->h_items[resultHash],
			hTable->h_items[resultHash]->h_next,
			hTable->h_items[resultHash]->h_next,
			hTable->h_items[resultHash]->h_key,
			hTable->h_items[resultHash]->h_key,
			hTable->h_items[resultHash]->h_value,
			hTable->h_items[resultHash]->h_value
			);
			node = node->h_next;
		}
	} while (++hNodePtr < hNodePtrZ); 
}

// insert multpile keys
//
int main(){
	HashTable *tableResult = h_create(10);
	assert(tableResult != NULL);
	
	HashNode  *nodeResult = h_insert(tableResult, "400", "101");
	assert(nodeResult != NULL);
	
	HashNode  *nodeResult2 = h_insert(tableResult, "401", "102");
	
	HashNode  *nodeResult3 = h_insert(tableResult, "400", "103");

	HashNode *searchResult = h_search(tableResult,"400");
	
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
