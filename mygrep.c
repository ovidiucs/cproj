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
		printf("%s:\t %s",fn, ret);
		//	fputs(data, stdout);
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
	char chbuf[1];
	char *ret;
	char* pat = argv[1];
	int rc = 0;
	
	if (argc > 2) {
		printf("The search term is: '%s' and the filename is: '%s'\n", argv[1], argv[2]);
		for ( int i = 2; i < argc; i++ ) {
			fn = argv[i];	
			fptr = fopen (fn, "r");
			if (fptr == NULL) {
				fprintf(stderr,"Unable to open %s\n", fn);
				exit(1);
			} else {
				rc = readfile(pat, fptr, fn);
			}
			fclose(fptr);
		}
	} else if (argc == 2) {
		printf("No filename argument specified.\nUsing standard input.\n");
		while (read(0, chbuf, sizeof(chbuf))>0) {
			ret = strstr(chbuf,pat);
			printf("%s\n%s\n%s\n",ret,chbuf,pat);
		}
	} else {
		printf("Usage: Specify a search term followed by a filename.\n");
		exit(0);
	}
	return rc;
}
