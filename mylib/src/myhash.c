#include <stdio.h>
#include <stdlib.h>
#include "../include/myhash.h"
#include "../include/mylib.h"

#define DEFAULT_HASH_SIZE 97

//  Free allocated memory for entire hash table
void h_free (HashTable *hash) {
	free(hash);
}

// Initializing a hash table
HashTable *h_create ( unsigned int size ) {
	// Create hash pointer (for malloc)
	HashTable *hash;

	if ( (hash = (HashTable *) malloc(sizeof(HashTable) ) ) == NULL ) {
		perror("malloc () failed");
		exit(1);
	}

	// if size is 0 then set the size to default
	if (size == 0)
		size = DEFAULT_HASH_SIZE;

	// calloc - allocate the array and init to null
	hash = (HashTable *) calloc( (size_t) size , sizeof(HashTable) );

	// return hash
	return hash;
}

// Insert a key-value pair into a hash table
void h_insert (HashTable *h_table, char *h_key, char *h_value) {

}

// Retrieve a key-value pair from a hash table
char *h_search (char *h_value, char *h_key) {

}
