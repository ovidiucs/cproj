#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>

static void dirPrint(char *dirpath, int indentLevel) {
	// read directory entries
	DIR *dirptr;
	dirptr = opendir(dirpath);
	struct dirent *ent;
	if (dirptr != 0)
		perror(NULL);
	// header print
	fprintf(stdout,"Directory tree of %s\n-----------------------\n", dirpath);
	// for each directory entry
	while ( (ent = readdir(dirptr) != NULL ) ) {
	fprintf(stdout,"%s\n",readdir(dirptr)->d_name);
		// print file to stdout
			// if file is a directory increase indentation (add space)
			// rerund same function with argument now as current directory
		}
	closedir(dirptr);
}

int main (int argc, char **argv) {
	int rc = 0;
	int ret = 0;

	struct stat fstat;
	//fstat->st_mode & S_IFDIR
	//fprintf(stderr,"Argument count is: %d\n", argc);
	//fprintf(stderr,"Argument 1 is: %s\n", argv[0]);
	//exit (0);
	if (argc != 2) {
		fprintf(stderr, "Usage: %s dir\n", argv[0]);
		rc = 1;

	} else {
		ret = stat(argv[1],&fstat);
		if (ret != 0)
			perror(NULL);
		else {
			if ( fstat.st_mode & S_IFDIR ) {
				fprintf(stderr, "This is a directory\n");
				fprintf(stderr, "Calling opendir\n");
				dirPrint(argv[1],1);
		}


		}
		// rest of code
	// call
	}
	return rc;

}
