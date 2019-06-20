#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myhash.h"
#include "mylib.h"

#define DEFAULT_HASH_SIZE 97

//  Free allocated memory for entire hash table
#if 0
void h_free (HashNode *hash) {
	free(hash->h_key);
	free(hash->h_value);
	free(hash);
}
#endif

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
	// Hold the prime number
	unsigned int primeSize = 0;

	if ( (hash = (HashTable *) malloc(sizeof(HashTable) ) ) == NULL ) {
		perror("malloc () failed");
		exit(1);
	}

	// if size is 0 then set the size to default
	if (size == 0)
		hash->h_size = DEFAULT_HASH_SIZE;
	else {
		primeSize = prime(size);
		if (primeSize == 0) {
			fprintf(stderr, "Can't get prime number for %d size\n", size );
			exit(1);
		}
		hash->h_size = primeSize;
	}
		
	// calloc - allocate the array and init to null

	hash->h_items = (HashNode**) calloc((size_t) size ,sizeof(HashNode*));
	if (hash->h_items == NULL) {
		perror("calloc () failed");
		exit(1);
	}
	
	// return hash
	return hash;
}

// Insert a key-value pair into a hash table

HashNode *h_insert (HashTable *hTable, char *key, char *value) {
	HashNode *newNode;

	int resultHash = hash(key,hTable->h_size);

	if ( (newNode = (HashNode *) malloc(sizeof(HashNode) ) ) == NULL ||
			(newNode->h_key = strdup(key) ) == NULL ||
			(newNode->h_value = strdup(value) ) == NULL ) {
			
		perror("malloc () failed for HashNode");
		exit(1);
	}

	newNode->h_next = hTable->h_items[resultHash];
	hTable->h_items[resultHash] = newNode;
	
	return newNode;
}

/*
// Retrieve a key-value pair from a hash table
// declare extern in myhash.h
// takes Hastable and key
// ret - HastNodes pointer 
HashNodes *h_search (HashTable *hTable, char *key) {
1. call hash function with key and table size
2. search down link list in the array element using strcmp to find node that matches key
3. return node that found or null if end of list
}
 */
//static HashTable *h_delete()
