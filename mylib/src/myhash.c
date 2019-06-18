#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/myhash.h"
#include "../include/mylib.h"

#define DEFAULT_HASH_SIZE 97

//  Free allocated memory for entire hash table
static void h_free (HashNode *hash) {
	free(hash->h_key);
	free(hash->h_value);
	free(hash);
}

// Hash a key and return integer result.

static size_t hash(char *key, int hashSize) {
    size_t k = 0;
    while(*key != '\0')
            k = (k << 2) + *key++;
    return k % hashSize;
}

// initialises a new hash table
// size - how many HashNodes we want to store
// default at 97 HashNodes
// initialise the array of items with calloc

HashTable *h_create ( unsigned int size ) {

	// Create hash pointer (for malloc)
	HashTable *hash;


	if ( (hash = (HashTable *) malloc(sizeof(HashTable) ) ) == NULL ) {
		perror("malloc () failed");
		exit(1);
	}

	// if size is 0 then set the size to default
	if (size == 0)
		hash->h_size = DEFAULT_HASH_SIZE;

	// calloc - allocate the array and init to null

	hash->h_items = (HashNode**) calloc((size_t) size ,sizeof(HashNode*));
	if (hash->h_items == NULL) {
		perror("calloc () failed");
		exit(1);
	}
	hash->h_size = size;

	// return hash
	return hash;
}

// Insert a key-value pair into a hash table

HashNode *h_insert (char *h_key, char *h_value) {
	HashNode *h_newNode;

	if ( (h_newNode = (HashNode *) malloc(sizeof(HashNode) ) ) == NULL ) {
			perror("malloc () failed for HashNode");
			exit(1);
	}

	h_newNode->h_key = strdup(h_key);
	h_newNode->h_value = strdup(h_value);
	h_newNode->h_next = NULL;

	return h_newNode;
}

/*
// Retrieve a key-value pair from a hash table

static HashTable *h_search (char *h_value, char *h_key) {

}
 */
//static HashTable *h_delete()

int main(){
	HashTable *h_result = h_create(10);

	HashNode *h_Nresult = h_insert("400", "101");

	int i = 0;


	char *strings[2];
	strings[0] = "aac";
	strings[1] = "ccc";
	strings[2] = "ddd";
	char *sndstring[2];
	sndstring[0] = "fff";
	sndstring[1] = "ggg";
	sndstring[2] = "hhh";

	do {
		int resultHash = hash(h_Nresult->h_key,h_result->h_size );
		if (h_result->h_items[resultHash] != NULL){
			fprintf(stderr, "A collision has occured");
			exit(1);
		} 
		// Otherwise add to the the index returnded by the hasing function
		h_result->h_items[resultHash] = h_Nresult;
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

	return 0;
}
