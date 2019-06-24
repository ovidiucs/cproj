#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/myhash.h"
#include "../include/mylib.h"

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
    unsigned int k = 0;
    while(*key != '\0')
            k = (k << 2) + (unsigned int) *key++;
    return k % (unsigned int) hashSize;
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
// Find a key in a given linked list

static HashNode *h_findKey(HashNode *hNode, char *key) {
	
	while (hNode != NULL) {
		if(strcmp(hNode->h_key,key) == 0) {

			break;
		}
	}
	return hNode;
}
 
// Insert a key-value pair into a hash table

HashNode *h_insert (HashTable *hTable, char *key, char *value) {
	HashNode *newNode;
	// result hash will give same index and that index will already have 
	// a node if there was a previous write here
	size_t resultHash = hash(key,hTable->h_size);

	newNode = hTable->h_items[resultHash];
	// overwrites pointer if two key are same. Collisions are overwritten
	// cannot use realloc (save old pointer if this is the case)
	//HashNode *oldNodePtr = newNode;
	newNode = h_findKey(newNode, key);


	// Executes only if the newNode is NULL-not visited before
    if ( newNode == NULL ) {	
		if ( (newNode = (HashNode *) malloc(sizeof(HashNode) ) ) == NULL ||
				(newNode->h_key = strdup(key) ) == NULL ||
				(newNode->h_value = strdup(value) ) == NULL ) {

			perror("malloc () failed for HashNode");
			exit(1);
		}
		// h_next will be null as the if executes when newNode is null
		newNode->h_next = hTable->h_items[resultHash];
		// the line below assumes the address is different - can be same if same hash
	 	hTable->h_items[resultHash] = newNode;
     } else {
 		// Keys are the same , reeuse key and assign a different value + 1 for '/0'
		// does not work as the value was not assigned from the argument to h_value
     	// newNode->h_value = (char *) realloc((void *) oldNodePtr->h_value, strlen(value)+1);
		 free(newNode->h_value);
		 newNode->h_value = strdup(value);
     }
			


	return newNode;
}

/*
// Retrieve a key-value pair from a hash table
// declare extern in myhash.h
// takes Hastable and key
// ret - HastNodes pointer
 */
HashNode *h_search (HashTable *hTable, char *key) {
	HashNode *newNode;

	//1. call hash function with key and table size
	size_t resultHash = hash(key,hTable->h_size);
	// the node to the hashed array index of the key 
	newNode = hTable->h_items[resultHash];
	// call findkey on the value found to get the key
	newNode = h_findKey(newNode, key);

	// return the pointer
	return newNode;
}