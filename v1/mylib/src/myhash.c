#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/myhash.h"
#include "../include/mylib.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define DEFAULT_HASH_SIZE 97
#define PATH_MAX 255
#define ARRAY_MAX 0.7
#define BUFF 2048
//  Free allocated memory for entire hash table
#if 0
#endif

// Hash a key and return integer result.

static size_t hash(char *key, unsigned int hashSize) {
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

	if ( (hash = (HashTable *) malloc(sizeof(HashTable) ) ) == NULL ) {
		perror("malloc () failed");
		exit(1);
	}

	// if size is 0 then set the size to default
	if (size == 0)
		hash->h_size = DEFAULT_HASH_SIZE;
	else {
		// Hold the prime number
		unsigned int primeSize = 0;
	
		primeSize = prime(size);
		if (primeSize == 0) {
			fprintf(stderr, "Can't get prime number for %d size\n", size );
			exit(1);
		}
		hash->h_size = primeSize;
	}
	 
	// calloc - allocate the array and init to null 
	// 01.08 - set the argument to calloc to be the size of the hash table 
	//		   not the size passed in the function call.
	
	hash->h_items = (HashNode**) calloc((size_t) hash->h_size ,sizeof(HashNode*));
	if (hash->h_items == NULL) {
		perror("calloc () failed");
		exit(1);
	}
	// set h_count to 0;
	hash->h_count = 0;
	// return hash
	return hash;
}

extern size_t cmpCount;

// Find a key in a given linked list
// called by h_insert and h_search and h_delete
static HashNode *h_findKey(HashNode *hNode, char *key) {
// increment a global variable to find out how many times strcmp has been called
	while (hNode != NULL) {
	cmpCount++;
		if(strcmp(hNode->h_key,key) == 0) {
			break;
		}
		hNode = hNode->h_next;
	}
	return hNode;
}
// h_resize called by h_insert in case the array gets too small and a new hash
// table will need to be created. 
HashTable *h_resize (HashTable *oldHashTable, unsigned int size) {
	
	// We will have to create a new HashTable first
	
	HashTable *biggerHashTable;
	biggerHashTable = h_create(size);
	fprintf(stderr,"Calculated new hash size is: %u\n",biggerHashTable->h_size);

	// We now have the zeroed array of pointers 
	// Next we need to re-index 

	// Assign first eleemnt in array of pointers from the old hash table
	HashNode **hNodePtr = oldHashTable->h_items;
	
	// The last element of the array of pointer will be the size defined in hNodePtrZ
	HashNode **hNodePtrZ = hNodePtr + oldHashTable->h_size;
	
	// A new hash node - can be null or something else
	HashNode *newNode;
	HashNode *oldNode;

	do {
		// Derefenrce one level and set it to node
		oldNode = *hNodePtr;
		// Check first if node is not null
		while (oldNode != NULL) {
			fprintf(stderr,"Value from oldNode, is: %s and key is: %s\n",oldNode->h_value,oldNode->h_key);
			HashNode* tempVar = oldNode->h_next;
			// Call h_insert to insert the data into the new bigger hash table.
			h_insert(biggerHashTable,oldNode->h_key,oldNode->h_value);
			// Assign the temporary variable which holds the next value which is not null
			// into old node. 
			oldNode = tempVar;
		// Transfer from old table to new table
		// oldnode is not not null
		// 1. grab  next pointer before move put it in a temp variable hashnode*
		// 2. move node to new hash table - find index, rehash key , etc
		// 3. oldnode = temp variable
		}
	} while (++hNodePtr < hNodePtrZ);
	// free old array
	free((void *) oldHashTable->h_items);
	//oldHashTable->h_items = biggerHashTable->h_items;
	//oldHashTable->h_size = biggerHashTable->h_size;
	*oldHashTable = *biggerHashTable;
	free((void *) biggerHashTable);
	
	return oldHashTable;
}

// Insert a key-value pair into a hash table
// until a given condition then call h_resize
HashNode *h_insert (HashTable *hTable, char *key, char *value) {
	HashNode *newNode;
	fprintf(stderr,"Begin h_insert with key %s\n", key);
	// result hash will give same index and that index will already have
	// a node if there was a previous write here
	size_t resultHash = hash(key,hTable->h_size);

	newNode = hTable->h_items[resultHash];
	// overwrites pointer if two key are same. Collisions are overwritten
	// todo: allow for hash collisions by pushing to the next value - not done 02.08
	
	// a) new node is null, increase counter of used array elements 
	// b) then if the number is greater than a given value 
	// c) we will need to create ask for a new block of memory in the heap 
	// and do a re-indexing on the keys on the new node 
	// after the new index is known then move the pointers from the old 
	// b)
	//fprintf (stdout,"%d\n",nodeCount);
	// cannot use realloc (save old pointer if this is the case)
	//HashNode *oldNodePtr = newNode;
	newNode = h_findKey(newNode, key);


	// Executes only if the newNode is NULL-not visited before
        if ( newNode == NULL ) {
        	hTable->h_count++;
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
	
		double quota1 = (double) hTable->h_count/hTable->h_size;
		// c) 
		if ( quota1 > ARRAY_MAX) {
			fprintf(stderr,"Resizing array\n quota is %f ",quota1);
			hTable = h_resize(hTable,(unsigned int) (hTable->h_size*(1+ARRAY_MAX)) );
		}
			//	fprintf (stdout,"%lu\n%lu\n",hTable->h_size*hTable->h_size,hTable->h_size);
			// calloc to allocate a new array with a new size
			// seprate functions - called from - resize and h_insert
			// keep existing hash table and change its array memeber
			// - newNode if condition - separate function
			// - and also the newNode = h_findKey
			// for each element in the current array / rehash to find new key in new array/
			// ---///--- create new function for resizing.

        } else {
 		// Keys are the same , reeuse key and assign a different value + 1 for '/0'
		// Latest value will be used for the key.
			newNode->h_value = (char *) realloc((void *) newNode->h_value, strlen(value)+1);
			newNode->h_value = strcpy(newNode->h_value,value);
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
/*
 * Deletes a hashNode*
 * params: - key, hashTable
 */
//    #include <string.h>

//        void *memset(void *s, int c, size_t n);

bool h_delete (HashTable *hTable, char *key) {
	// node 1 pointing to node priror to it
	// node 2 is the current node we're on
	HashNode *node1, *node2;
	size_t resultHash = hash(key,hTable->h_size);
	node1 = NULL;
	node2 = hTable->h_items[resultHash];

	
	while (node2 != NULL) {
	
		if(strcmp(node2->h_key,key) == 0) {
			// remove the node
			free((void *) node2->h_key);
			free((void *) node2->h_value);
			if (node1 == NULL) {
				hTable->h_items[resultHash] = node2->h_next;				
			} else  {
				node1->h_next = node2->h_next;					
				// unlink from within the list and then do free and return
				
				// set node1 pointer to node2 next pointer
			}
			free((void *) node2);
			hTable->h_count--;
			return true;
		}
		node1 = node2;
		node2 = node2->h_next;	
	}
	
	return false;
	//free((void *) hash);

}
