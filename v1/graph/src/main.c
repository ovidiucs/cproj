#include <stdlib.h>

#1. Define data strucutres

typedef struct {
	char *name;
	Edge *edges[];
	char *vendor;
} Node;

enum edgeType {
	red,
	blue,
	green
}

typedef struct { 
	enum edgeType color;
	bool logical;
		
} Edge1;

Edge1 example[] = {
	red,"Link to r2";
	blue,"link to r3";
	red,1;
}

typedef struct {
	char *name;
	unsigned long speed;
	unsigned int delay;
	unsigned int cost;
} Edge2;

typedef struct {
	int type;
	Node *endpoint1;
	Node *endpoint2;
	char *rtrPortA;
	char *rtrPortB;
	union {	
		Edge1 e1;	
		Edge2 e2;	
	} edgeVal;
} Edge;

