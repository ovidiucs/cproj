#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

//
#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

static int readLn(char *fn, char *flags, char* mode){

}

int main(int argc, char** argv) {
    // check number of arguments
    //1. Open the file (or create it)
    // returns integer for the file descriptor,
    // non negative, takes a char pointer to a filename and flags
    // a file descriptor is a reference to an open file description
    int inputFd = 0;
    int outputFd = 0;
    int flags = 0;

    if(argc > 2) {
        fprintf(stderr,"Usage: %s [filename]\n",argv[0]);
    } else if (argc == 2){
        fprintf(stderr, "Using file file: %s\n", argv[1]);
        inputFd = open(argv[1],O_RDONLY);
        if(inputFd == -1){
            errno;
        }
        outputFd = read(inputFd,BUF_SIZE,1);
        
    } else {
        fprintf(stderr, "reading from stdin\n");
    }
    //
}
