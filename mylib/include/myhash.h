// Header file for hash routine


// Associative array
// Also called a map, symbol table or dictionary.

typedef struct HashNode {
	// Next node in the key collision list.
	struct HashNode *h_next;
	char *h_key;
	char *h_value;
} HashNode;

// the hash table stores an array of pointers to items
// and some details about its size
typedef struct  {
	HashNode **h_items;
	unsigned int h_size;
} HashTable;

extern HashNode *h_insert (HashTable *hTable, char *key, char *value);
extern HashTable *h_create ( unsigned int size );
extern HashNode *h_search (HashTable *hTable, char *key);
extern void h_delete (HashTable *hTable, char *key);
