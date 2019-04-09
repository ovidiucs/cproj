#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const char *myarg = NULL;

int readfile() {
	char *ret;
	const char searchedTerm[20] = "This";
	const char textsearched[100] = "This is free software: you are free to change and redistribute it.";

	ret = strstr(textsearched,searchedTerm);
	printf("The substring is: %s\n");

	return 0;
}

int main(int argc, char *argv[]) {

// Declare pointer to file for use later
	FILE *fptr;
	char ch;
	myarg = argv[1];
#if 0
	if (argc == 3 ){
		printf("The search term is %s and the filename is '%s'\n", argv[1], argv[2]);
		fptr = fopen (argv[2], "r");
	} else {
		printf("Usage: Specify a search term followed by a filename.\n");
		exit(0);
	}
#endif

	if (fptr == NULL) {
	// Empty file	
			printf("Unable to open specified file\n");
			exit(1);
	} else {
		//int rc = readfile(fptr,argv[1]);
		int rc = readfile();
		printf ("%s",rc);
#if 0
		// fgetc - return the character currently pointed by the
		// internal file position. internal file position is then adv
		// anced to the next character
			while((ch=fgetc(fptr))!=EOF) {
			printf("%c", ch);
#endif
	}	
	fclose(fptr);
	return 0;
}

