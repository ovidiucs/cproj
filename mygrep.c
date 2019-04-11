#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int readfile(char *argument, FILE **fptr) {
	char data[1000];
	char* ret;
	char* s2 = argument;

	while(fgets (data,1000,*fptr) != NULL) {
	ret = strstr(data,s2);
	if (ret != NULL) {
	printf("The substring in s1 is %s and in s2 is %s and the returned is %s\n",data,s2,ret);
		}
	}
	return 0;
}

int main(int argc, char **argv) {

	FILE *fptr;
	char* myarg = argv[1];
	if (argc == 3) {
		printf("The search term is '%s' and the filename is '%s'\n", argv[1], argv[2]);
		fptr = fopen (argv[2], "r");
	} else {
		printf("Usage: Specify a search term followed by a filename.\n");
		exit(0);
	}

	if (fptr == NULL) {
			printf("Unable to open specified file\n");
			exit(1);
	} else {

		int rc = readfile(myarg, &fptr);
	}

	return 0;
}
