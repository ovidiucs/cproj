#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

static void dirPrint(dirpath, int indentLevel) {
	// read directory entries

	// header print
	// Directory tree of X
	// for each directory entry
		// print file to stdout
			// if file is a directory increase indentation (add space)
			// rerund same function with argument now as current directory

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
			if ( fstat.st_mode & S_IFDIR )
				fprintf(stderr, "This is a directory\n");
		}
		// rest of code
	// call
	}
	return rc;

}
