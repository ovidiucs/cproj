#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "../include/myhash.h"
// edit library implement search func.
// test h_search - call on same keys and verify that is same result as the initial call to insert
static char *readFile(char *fn);

struct Tuple {
    char *key;
    char *value;
};

static void dumpTable (HashTable *table, bool verbose) {
	// Scope - take a hashTable and iterate through each array element with each
	// element containing pointers to has nodes; in essence containing a linked list

	// First eleemnt in array of pointers will be the first node
	// HashNode **hNodePtr == &hNodePtr[i]
	HashNode **hNodePtr = table->h_items;
	// The last element of the array of pointer will be the size defined in the
	HashNode **hNodePtrZ = hNodePtr+ table->h_size;
	// A new nash node - can be null or something else
	HashNode *node;

		fputs("HASHTABLE DUMP \n",stderr);
		do {
			// Derefenrce one level and set it to node
			node = *hNodePtr;
			// Check first if node is not null - don't print info
				while (node != NULL) {
				if (verbose) {
					fprintf(stdout, "De-ref the pointer at %p we have our nosde linked list with values:\n\
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
				} else {
					fprintf(stdout,"%s:%s\n",(void *)node->h_key,(void *)node->h_value);
				}
				// Set node to the next pointer
				node = node->h_next;
				//fprintf(stderr,"Key is: %s, Value is: %s\n",found,str1+1);
		// Increase by one element inside the array (move by one array bucket )
		}
	} while (++hNodePtr < hNodePtrZ);

}

// insert elements into hash table

static char *t_parseBuff (char *fptr) {
	// Don't pass NULL filename
	assert(fptr);
	char *save = fptr;
	// found - the string from \0 to \0
	char *found = NULL;
	// str1 the value in the key-value
	char *str1 = NULL;
	while ( (found = strsep(&fptr, "\n")) != NULL) {
		str1 = strchr(found,':');
		if (str1 == NULL)
			continue;
		*str1 = '\0';
	}
	return save;
}
//
// Returns key value pair - returns bool. 
// Arguments: struct Tuple pointer, indirect buffer pointer
 
static bool kv_format(struct Tuple *tptr,char **fptr){
	char *fptr1 = *fptr;
	char *str = NULL;
	// If the beginning of the buffer (next key which we want to read) is a null byte
	// then return false	
	if (*fptr1 == '\0')
		return false;
	// Otherwise set the key and the value of the caller's struct
	tptr->key = fptr1;
	str = strchr(fptr1, '\0');
	tptr->value = str + 1;
	*fptr = strchr(str + 1, '\0') + 1;
	return true;
}

// readfile
static char *readFile(char *fn) {
	// from https://stackoverflow.com/questions/3463426/in-c-how-should-i-read-a-text-file-and-print-all-strings
 	// FILE handle
	assert(fn != NULL);
	FILE *stream;
	stream = fopen(fn, "r");

	// buffer
	char *buf = NULL;
	size_t readSize;

	if (stream) {
		struct stat s;
		fstat(fileno(stream),&s);

		// Allocate string that can hold all of the data
		// includes + 1 for null character + 1 to codfy end of file for Tuple
		buf = (char *) malloc(sizeof(char) * (s.st_size + 2));

		// read
		readSize = fread(buf, sizeof(char), s.st_size, stream);

		// append null at end
		buf[s.st_size] = '\0';
		buf[s.st_size+1] = '\0';
		// something is not right free resources
		if (s.st_size != readSize) {
			free(buf);
			buf = NULL;
			perror("fread failure");
			exit(1);
		}
		// close the stream
		fclose(stream);
	//close file at end
	} else {
			perror("Open failed");
			exit(1);
	}
	return buf;
}

// insert multpile keys
//

int main(int argc, char** argv){
	HashTable *tableResult = h_create(10);
	assert(tableResult != NULL);

	// initialise filename to NULL
	char *fileRead = NULL;
	
	char *format,*format0;
	
	struct Tuple kv_tuple;	
	
	if (argc != 2) {
		fprintf(stderr,"Usage: %s <filename>\n", argv[0]);
	} else {
		char *fn = argv[1];

		// fileread from filename
		fileRead = readFile(fn);
		format = t_parseBuff(fileRead);
		format0 = format;
		
		while (kv_format(&kv_tuple,&format)) {
			h_insert(tableResult,kv_tuple.key, kv_tuple.value);	
		}
		int counter = 0;
		format = format0;
		while (kv_format(&kv_tuple,&format)) {
			h_delete(tableResult,kv_tuple.key);
			if(++counter ==  50)
				break;
			}
				
	}
	dumpTable(tableResult,0);

	return 0;
}
