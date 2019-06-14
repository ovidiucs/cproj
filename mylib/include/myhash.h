// Header file for hash routine


typdef struct HashNode {
	// Next node in the key collision list.
	struct HashNode *h_next;
	char *h_key;
	char *h_value;
} HashNode;

typedef struct {
	HashNode **h_table;
	unsigned int h_size;
} Hash;

