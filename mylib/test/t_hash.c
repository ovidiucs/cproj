#include "../include/myhash.h"
// edit library implement search func.
// test h_search - call on same keys and verify that is same result as the initial call to insert

// insert multpile keys
//
int main(){
	HashTable *tableResult = h_create(10);
//
	HashNode  *nodeResult = h_insert(tableResult, "400", "101");
//	HashNode  *nodeResult = h_insert(tableResult, "400", "101");
	HashNode  *nolt = h_insert(tableResult, "400", "101");

	HashNode *searchResult = h_search(tableResult,"400");
#if 0
	int i = 0;


	char *strings[2];
	strings[0] = "aac";
	strings[1] = "ccc";
	strings[2] = "ddd";`
	char *sndstring[2];
	sndstring[0] = "fff";
	sndstring[1] = "ggg";
	sndstring[2] = "hhh";

	do {
		// Otherwise add to the the index returnded by the hasing function
		// Will print
	fprintf(stderr,"Struct HashTable address: %p, HashNode** : %p, HashNode* : %p, hash->h_items[%d]: %p\n\n",
					h_result,
					h_result->h_items,
					h_result->h_items[resultHash],
					resultHash,
					h_result->h_items[resultHash]
					);
	fprintf(stderr,"Struct HashNode address: %p, HashNode value: %s, HashNode key: %s, HashNode next: %p\n",
					h_Nresult,
					h_Nresult->h_value,
					h_Nresult->h_key,
					h_Nresult->h_next
					);
		// Set i to...
		i +=1;
		// While condition is bad
	} while (h_result->h_items[i]  != NULL);

#endif
	return 0;
}
