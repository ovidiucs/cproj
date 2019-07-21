#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "../include/myhash.h"
// edit library implement search func.
// test h_search - call on same keys and verify that is same result as the initial call to insert

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
				fprintf(stderr, "De-ref the pointer at %p we have our nosde linked list with values:\n\
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
			node = node->h_next;
		}
	// Increase by one element inside the array (move by one array bucket )
	} while (++hNodePtr < hNodePtrZ);
	
}

// readfile
char *readFile(char *fn) {
	// from https://stackoverflow.com/questions/3463426/in-c-how-should-i-read-a-text-file-and-print-all-strings
	// FILE handle
	FILE *stream;
	stream = fopen(fn, "r");

	// buffer
	char *buf = NULL;
//	size_t stringSize;
	size_t readSize;
	
	if (stream) {
		// Seek last bytes on the stream
//		fseek(stream, 0, SEEK_END);
		// get current value of file position
//		stringSize = ftell(stream);
		// rewind to the start of the file
//		rewind(stream);

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
(char *) fn = 0x00007fffffffedaf "../testdata"
(char *) buf = 0x0000000000000000
(FILE *) stream = 0x00005555555592e0
(size_t) s.st_size = 115322
(size_t) readSize = <variable not available>

#endif
// insert multpile keys
//


int main(int argc, char** argv){
	HashTable *tableResult = h_create(10);
	assert(tableResult != NULL);
	// The pointer to the line which was read
	//char *line = NULL;
	//size_t len = 0;
	//ssize_t nread;

	// filename
	char *fn = argv[1];

	if (argc != 2) {
		fprintf(stderr,"Usage: %s <filename>\n", argv[0]);
	} else {
		char *fileRead = readFile(fn);
		//char *string = strsep(&fileRead,":");
		char *found;
		size_t counter = 0;
		char *str1;
		while ( (found = strsep(&fileRead, "\n")) != NULL) {
			str1 = strchr(found,':');
			if (str1 == NULL) {
				fprintf(stderr, "No colon was found %s\n",found);
			}
			else {
				*str1 = '\0';
				fprintf(stderr,"Key is: %s, Value is: %s\n",found,str1+1);
				h_insert(tableResult, found,str1+1);
			}

		}
	}
	#if 0
	hashnode  *noderesult = h_insert(tableresult, "400", "101");
	assert(noderesult != null);

	hashnode  *noderesult2 = h_insert(tableresult, "401", "102");
	hashnode  *noderesult3 = h_insert(tableresult, "400", "1034444444444444");
	dumptable(tableresult);
	printf("________________\n");
	hashnode *searchresult = h_search(tableresult,"400");
	h_delete(tableresult,"400");
	1. read file
	2. delete first 50 keys
	3. write out hastable to stdout, key: value\n
	4. quit / from shell cut first 50 lines from the input file and take rest of file, sort it, save to tmp file
	take output of program and sort it then compare the tmp file and output provided by program. 
	# endif
	dumpTable(tableResult);
	return 0;
}
