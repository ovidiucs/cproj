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

	size_t resultHash = hash(key,hTable->h_size);
	newNode = hTable->h_items[resultHash];
	newNode = h_findKey(newNode, key);
	
    if ( newNode == NULL ) {	
	if ( (newNode = (HashNode *) malloc(sizeof(HashNode) ) ) == NULL ||
			 (newNode->h_key = strdup(key) ) == NULL ||
			 (newNode->h_value = strdup(value) ) == NULL ) {

		perror("malloc () failed for HashNode");
		exit(1);
	}
	newNode->h_next = hTable->h_items[resultHash];
	hTable->h_items[resultHash] = newNode;
     } else {
 		// Key exists , reeuse key + 1 for '/0'
     			newNode->h_value = (char *) realloc((void *) newNode->h_value, strlen(value)+1);
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
	newNode = hTable->h_items[resultHash];
	newNode = h_findKey(newNode, key);

	return newNode;
}
#if 0
	// 1a. arguments for strcmp
	char *keyStrAtIndex = hTable->h_items[resultHash]->h_key;
	
	// 1b. nextvalue local variable
	HashNode *nextValue = hTable->h_items[resultHash]->h_next;
	
	// 2. set return value to a friendly variable
	HashNode *returnVar = hTable->h_items[resultHash];

	fprintf(stderr, "'resultHash' is %zu for 'key' %s\n", resultHash, key);
//2. search down link list in the array element using strcmp to find node that matches key
  fprintf(stderr, "The hashtable table is at memory address: %p\n",hTable);
	fprintf(stderr, "at index %zu in hastable we have the memory address %p that goes to our node \n", resultHash, hTable->h_items[resultHash] );
	/*
(lldb) print hTable->h_items[5]
(HashNode *) $11 = 0x00005555555592e0
(lldb) print *hTable->h_items[5]
(HashNode) $12 = {
  h_next = 0x0000000000000000
  h_key = 0x0000555555559300 "400"
  h_value = 0x0000555555559320 "101"
}
 */
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
		if ( (nextValue == NULL) && (strcmp(keyStrAtIndex,key) == 0) )
					fprintf(stderr, "They are the same\n");
		else {
				// looking for the key inside the next element of the linked list
				char* keyAtNextValue = hTable->h_items[resultHash]->h_next->h_key;
				while( nextValue != NULL)  {
					fprintf(stderr, "Found a collision, traversing Linked list at address %p, key is: %s\n",
							 nextValue, nextValue->h_key);
					nextValue = nextValue->h_next;
				}
		}
//		fprintf(stderr,"%s", )
//3. return node that found or null if end of list
	return returnVar;
}

//static HashTable *h_delete()
#endif
