#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const char *myarg = NULL;

int readfile(char *argument) {
	printf("%s\n", argument);
	char* ret;
	char* s2 = argument;
	char s1[100] = "This is free software: you are free to change and redistribute it.";

	ret = strstr(s1,s2);
	printf("The substring in s1 is %s and in s2 is %s and the returned is %s\n",s1,s2,ret);

	return 0;
}

int main(int argc, char *argv[]) {

// Declare pointer to file for use later
#if 0
	FILE *fptr;
	char ch;
	myarg = argv[1];
	
		printf("The search term is %s and the filename is '%s'\n", argv[1], argv[2]);
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
#endif
		//int rc = readfile(fptr,argv[1]);
		char *argument = argv[1];
		int rc = readfile(argument);
		//printf (rc);
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
