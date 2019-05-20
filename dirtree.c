#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

static void dirPrint(char *dirpath, int indentLevel) {
	// read directory entries

	DIR *dirptr;
	struct dirent *ent;
	
	if ( ( dirptr = opendir(dirpath) ) == NULL) {
		perror(dirpath);
		exit(1);
	}
	// header print
	fprintf(stdout,"Directory tree of %s\n-----------------------\n", dirpath);
	// for each directory entry
	while ( ( ent = readdir(dirptr) ) != NULL )  {

	 	// fprintf(stdout,"%s\n",readdir(dirptr)->d_name)
		if (ent->d_type == DT_DIR) {
			if ( strcmp(".", ent->d_name) == 0 || strcmp("..",ent->d_name) == 0) {
				continue;
			}
			// length of current directory +1 for '/' + strlen of dir entry + /0
			char tempDir[strlen(dirpath)+1+strlen(ent->d_name)+1];
			
			sprintf(tempDir, "%s/%s", dirpath,ent->d_name);	
			dirPrint(tempDir,indentLevel+1);
			
		}
		
		for (int i = indentLevel; i >	 0 ; i--) {
			fputs("..", stdout);
		}
		fprintf(stdout,"| %s \n",ent->d_name);
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
				dirPrint(argv[1],0);
		}


		}
		// rest of code
	// call
	}
	return rc;

}
