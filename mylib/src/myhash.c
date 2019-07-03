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
#define BUFF 2048
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
// called by h_insert and h_search and h_delete
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
	// todo: allow for hash collisions by pushing to the next value

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

void h_delete (HashTable *hTable, char *key) {
	size_t resultHash = hash(key,hTable->h_size);
	HashNode *freeNode;
	HashNode *emptyMpde = NULL;

	freeNode = h_search(hTable,key);
	//fprintf(stderr, "%d", sizeof(freeNode));
	//free(freeNode->h_key);
	//free(freeNode->h_value);
	// this deletes the values and key but does not clear the pointers
	freeNode->h_key = (char *) memset((void *)freeNode->h_key, 0, sizeof(freeNode->h_key));
	freeNode->h_value =  (char *) memset((void *)freeNode->h_value, 0, sizeof(freeNode->h_value));
	//&freeNode = (HashNode *) memset((HashNode *)freeNode, 0, sizeof(freeNode));
	 hTable->h_items[resultHash] = emptyMpde;
	 free(freeNode);
	 /*
	 * (lldb) p *hTable->h_items[5]
	 * (HashNode) $70 = {
   * h_next = 0x0000000000000000
   * h_key = 0x0000555555559300 "400"
   * h_value = 0x0000555555559320 "1034444444444444"
   * }
	 * lldb)  p hTable->h_items[4]
   * (HashNode *) $87 = 0x0000000000000000
	 * (lldb)  p hTable->h_items[5]
	 * (HashNode *) $81 = 0x00005555555592e0
	 * (lldb)  p &hTable->h_items[5]
   * (HashNode **) $83 = 0x00005555555592a8
	 */
}
int openFile (const char *fn) {
		// Return value for open()
		int inputFd;

		// set fd and check it
		if ( ( inputFd = open(fn,O_RDONLY) )  < 0){
			perror("Error on open");
			return -1;

		}
		return inputFd;
}
/*
void readFile (int fd) {
	// Read bytes from fd int numRead for read () 3rd arg
	int countRead;

	// Output file descriptor
	int outputFd = 1; // stdout

	// Set buffer for void *buf arg
	char buf[BUFF];
	// extra buffer to fill end of line.
	//char extraBuffer
	// Keep track of offset after each '\n'
	//off_t offset = 0;

	// store last string until '\m'
	//if
	//off_t lseek(int fd, off_t offset, int whence);
	//off_t newPos = lseek(fd,,SEEK_DATA)
	while ( (countRead = read (fd, buf, BUFF)) > 0)
	  //pch = strtok (buf,":");
	  //fprintf(stderr,"%s\n\n\t\n",buf);
			if (write(outputFd, buf, countRead) != countRead)
				fprintf(stderr,"Could not write whole buffer.\n");
	//fprintf(stderr,"%s", pch);
}

 * readline `sz` bytes from file `fn`, begin at file `offset`
 * storing all chars in `buf`. `buf` is terminated at the first
 * newline found .
 * return -1 on error, EOF with 0 chars read , success number of chars read
 */


ssize_t readLine(char *buf, size_t sz, char *fn, off_t 	*offset){
	// Open the file as read only
	int fd = openFile(fn);

	ssize_t nchr = 0;
	ssize_t idx = 0;
	char *p  = NULL;

	/* position fd & read line */
	if ( (nchr = lseek(fd, *offset, SEEK_SET)) !=-1  )
		nchr  = read (fd, buf, sz);
	closeFile(fd);

	/* read error */
	if (nchr == -1)
		fprintf(stderr, "%s(), error: read failure in '%s'.\n", __func__, fn);

	/* end of file - no characters read */
	if (nchr == 0)
		return -1;

	/* check each character */
	p = buf;
	while( (idx < nchr) && (*p != '\n') )
				p++, idx++;
	*p = 0;

	/* newline not found */
	if (idx == nchr) {
		*offset += nchr;

		/* check file for missing newline at end */
		return nchr < (ssize_t) sz ? nchr : 0;

	}
	// set *offset to 1+idx
	*offset += idx + 1;

	return idx;
}

int closeFile(int fd){
	int closeFd;
	if ( (closeFd = close(fd)) < 0)
			perror("Error on close\n");
	else if(closeFd == 0) {
			fprintf(stderr, "Closed file descriptior\n");
		return closeFd;
	}
}
