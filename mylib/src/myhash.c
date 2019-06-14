#include <stdio.h>
#include "myhash.h"
#include "mylib.h"

#define DEFAULT_HASH_SIZE 97

//  Free allocated memory for entire hash table
void h_free (Hash *hash) {

};

// Initializing a hash table
Hash *h_create ( unsigned int size  ) {
	// Create hash pointer (for malloc)
	Hash *hash;
	
	if ( (hash = (Hash *) malloc(sizeof(Hash) ) ) == NULL ) {
		perror("malloc () failed");
		exit(1);
	}

	if (size == 0)
		size = DEFAULT_HASH_SIZE;

	// calloc - allocate the array and init to null
	// return hash
}

// Insert a key-value pair into a hash table
h_add(

// Retrieve a key-value pair from a hash table
h_find(
