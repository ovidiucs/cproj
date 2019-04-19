#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int readfile(char *pat, FILE *fptr, char *fn ) {
	char data[1000];
	char* ret;
	char* s2 = pat;

	while(fgets (data,sizeof(data),fptr) != NULL) {
		ret = strstr(data,s2);
		if (ret != NULL) {
		fprintf(stderr,"%s:\t %s",fn, ret);
		}
	}
	if (ferror(fptr)) {
		fprintf(stdout,"Error reading file %s\n", strerror(errno));
		exit(1);
	}
	return 0;
}

int main(int argc, char **argv) {
	
	FILE *fptr;
	char* fn;
	char chbuf[1024];
	char *ret;
	char* pat = argv[1];
	int rc = 0;
	
	if (argc > 2) {
		fprintf(stderr,"The search term is: '%s' and the filename is: '%s'\n", argv[1], argv[2]);
		for ( int i = 2; i < argc; i++ ) {
			fn = argv[i];	
			fptr = fopen (fn, "r");
			if (fptr == NULL) {
				fprintf(stderr,"Unable to open %s\n", fn);
				rc = 1;
			} else {
				rc = readfile(pat, fptr, fn);
			}
			fclose(fptr);
		}
	} else if (argc == 2) {
		fprintf(stderr,"No filename argument specified.\nUsing standard input.Use ^C to exit\n");
		rc = readfile(pat,stdin,0);
			
	} else {
		fprintf(stderr,"Usage: Specify a search term followed by a filename.\n");
		rc = 0;
	}
	return rc;
}
