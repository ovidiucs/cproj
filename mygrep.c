#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//const char *myarg = NULL;

int readfile(char *argument, FILE **fptr) {
	char data[1000];
	char* ret;
	//char* s1 = *fptr;
	char* s2 = argument;

	while(fgets (data,1000,*fptr) != NULL);
	ret = strstr(data,s2);
	printf("The substring in s1 is %s and in s2 is %s and the returned is %s\n",data,s2,ret);

	return 0;
}

int main(int argc, char **argv) {

// Declare pointer to file for use later

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
	// Empty file
			printf("Unable to open specified file\n");
			exit(1);
	} else {

		//int rc = readfile(fptr,argv[1]);
		int rc = readfile(myarg, &fptr);
		//printf (rc);
	}

#if 0
		// fgetc - return the character currently pointed by the
		// internal file position. internal file position is then adv
		// anced to the next character
			while((ch=fgetc(fptr))!=EOF) {
			printf("%c", ch);
	}
	fclose(fptr);
#endif
	return 0;
}
