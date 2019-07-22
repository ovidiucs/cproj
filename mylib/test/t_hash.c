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
					fprintf(stdout,"Key is: %s, Value is: %s\n",(void *)node->h_key,(void *)node->h_value);
				}
				// Set node to the next pointer
				node = node->h_next;
				//fprintf(stderr,"Key is: %s, Value is: %s\n",found,str1+1);
		// Increase by one element inside the array (move by one array bucket )
		}
	} while (++hNodePtr < hNodePtrZ);

}

// insert elements into hash table
kvpair *t_kvp(char *fptr) {
	// Don't pass NULL filename
	assert(fptr != NULL);
	kvpair *kvp;
	assert(kvp != NULL);
	// found - the string from \0 to \0
	char *found = NULL;
	// str1 the value in the key-value
	char *str1 = NULL;
	//strsep
	while ( (found = strsep(&fptr, "\n")) != NULL) {
		str1 = strchr(found,':');
		if (str1 == NULL) {
			fprintf(stderr, "No colon was found %s\n",found);
			continue;
		}
		else {
			// now format will be  "key"\0"value"\0"key"\0...
			*str1 = '\0';
			// and insert the key and value into the hash table
			kvp->key = found;
			kvp->value = str1+1;
		}
	}
	return kvp;
}

// remvoe elements from hashtale
#if 0
static void t_hdelete(HashTable *ht, int keys, char *fptr) {
	// operate a delet on an already allocated data

	// Don't pass nothing
	assert( (ht != NULL) && (fptr != NULL) );
	// read first 50 keys;
	char *found = NULL;
	fprintf(stderr, "%s", fptr);

	//for (i < keys)
	//h_delete(ht,key)

}
#endif

// readfile
static char *readFile(char *fn) {
	// from https://stackoverflow.com/questions/3463426/in-c-how-should-i-read-a-text-file-and-print-all-strings
	// FILE handle
	assert(fn != NULL);
	FILE *stream;
	stream = fopen(fn, "r");

	// buffer
	char *buf = NULL;
//	size_t stringSize;
	size_t readSize;

	if (stream) {
		struct stat s;
		fstat(fileno(stream),&s);

		// Allocate string that can hold all of the data
		// includes + 1 for null character
		buf = (char *) malloc(sizeof(char) * (s.st_size + 1));

		// read
		readSize = fread(buf, sizeof(char), s.st_size, stream);

		// append null at end
		buf[s.st_size] = '\0';
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
#if 0

#endif
// insert multpile keys
//

int main(int argc, char** argv){
	HashTable *tableResult = h_create(10);
	assert(tableResult != NULL);

	// initialise filename to NULL
	char *fileRead = NULL;
	if (argc != 2) {
		fprintf(stderr,"Usage: %s <filename>\n", argv[0]);
	} else {
		char *fn = argv[1];
		// fileread from filename
		fileRead = readFile(fn);
		//t_hinsert(fileRead,tableResult);
		//t_hdelete(tableResult,50,fileRead);
			//	fprintf(stderr,"%s,%s\n");

		//t_hinsert(fileRead,tableResult);
		kvpair *pairs = t_kvp(fileRead);
	//t_kvp(fileRead);
		fprintf(stderr,"%s,%s\n",pairs->key,pairs->value);
		//fprintf(stderr,"%s,%s\n",key,value);
			//h_insert(tableResult, key,value);

	}
	#if 0
	hashnode *searchresult = h_search(tableresult,"400");
	h_delete(tableresult,"400");
	1. read file
	2. delete first 50 keys
	3. write out hastable to stdout, key: value\n
	4. quit / from shell cut first 50 lines from the input file and take rest of file, sort it, save to tmp file
	take output of program and sort it then compare the tmp file and output provided by program.


	# endif
	dumpTable(tableResult,0);

	return 0;
}
