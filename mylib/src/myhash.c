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
	fprintf(stderr,"Struct HashTable address: %p, Hash Size: %d,\n HashNode** : %p HashNode* : %p, hash->h_items: %ld\n",
					hash, hash->h_size, hash->h_items,hash->h_items,sizeof(hash->h_items));

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
		fprintf(stderr,"Struct HashNode address: %p Value: %s Key: %s, Next: %p\n",
					h_newNode, h_newNode->h_value,h_newNode->h_key,h_newNode->h_next);

	return h_newNode;
}

/*
// Retrieve a key-value pair from a hash table

static HashTable *h_search (char *h_value, char *h_key) {

}
 */
//static HashTable *h_delete()

int main(int argc, char **argv){
	h_create(0);
	h_insert("400", "101");
	return 0;
}
