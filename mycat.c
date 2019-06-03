#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

//
#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

static void readLn(char *fn){
        // open will set this to whatever FD is needed
        int inputFd;

        // output fd 0 ' stdin 1 to stdout 2 to stderror
        int outputFd = 2;

        // how many bytes are read are stored here ; 0 is EOF
        ssize_t bufread = 0;
	
        // store buffer into an array of size BUF_SIZE
        char buf[BUF_SIZE];

        // A) Open the file - provide char* to filename, mode)
        // B) if inputFd is < 0 then return error
        if(fn == NULL){
		inputFd = STDIN_FILENO;
        } else {
		inputFd = open(fn,O_RDONLY);
		if (inputFd < 0) {
			perror("open() failed");
			exit(1);
		}
        }

        
        // C) the file position will advance by the number of bytes
        // read by read() it is not an error if this number is smaller
        // then the bytes requested
        // arguments - file descriptor, void * to buffer, size_t count)
        
        for (;;) {
        	
		if( (bufread = read(inputFd,buf,BUF_SIZE) ) < 0) {
			perror("read() failed");
			exit(1);
		} else {
		   if (bufread == 0)
			break;
		}	
        // write up to bytes from the buffer to the file descriptor
        // returns number of bytes written.
		
           if (write(STDOUT_FILENO,buf,(size_t) bufread) != bufread ) {
           	perror("write() failed");
           	exit(1);
           }
		
        }
}

int main(int argc, char** argv) {
    // check number of arguments
    //1. Open the file (or create it)
    // returns integer for the file descriptor,
    // non negative, takes a char pointer to a filename and flags
    // a file descriptor is a reference to an open file description

    // if program is invoked with -h
    // printussage and quit
    // otherwise assume all arguments are filenames
 
    if (argc == 1 ) {
	fprintf(stderr, "reading from stdin\n");
        readLn(NULL);
    } else if (! strcmp(argv[1],"-h") )
        	fprintf(stderr,"Usage: %s [filename]\n",argv[0]);
    else {
	char **argvPtr = argv + argc;
    
    	for ( ++argv ; argv < argvPtr ; argv++ ) {  
        	fprintf(stderr, "Showing file: %s\n", *argv);
        	readLn(*argv);
    	}
    }

    return 0;
}
