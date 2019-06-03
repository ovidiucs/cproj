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

static void readLn(char *fn, int mode){
        // open will set this to whatever FD is needed
        int inputFd = -1;

        // output fd 0 ' stdin 1 to stdout 2 to stderror
        int outputFd = 2;

        // how many bytes are read are stored here ; 0 is EOF
        int bufread = 0;

        // store buffer into an array of size BUF_SIZE
        char buf[BUF_SIZE];

        // A) Open the file - provide char* to filename, mode)
        inputFd = open(fn,mode);

        // B) if inputFd is < 0 then return error
        if(inputFd == -1){
            errno;
        }
        // C) the file position will advance by the number of bytes
        // read by read() it is not an error if this number is smaller
        // then the bytes requested
        // arguments - file descriptor, void * to buffer, size_t count)
        while( (bufread = read(inputFd,buf,BUF_SIZE) ) != 0){

        // write up to bytes from the buffer to the file descriptor
        // returns number of bytes written.

            write(1,buf,bufread);

        }
}

int main(int argc, char** argv) {
    // check number of arguments
    //1. Open the file (or create it)
    // returns integer for the file descriptor,
    // non negative, takes a char pointer to a filename and flags
    // a file descriptor is a reference to an open file description


    if (argc > 2) {

        fprintf(stderr,"Usage: %s [filename]\n",argv[0]);
    } else if (argc == 2){
        fprintf(stderr, "Showing file: %s\n", argv[1]);
        readLn(argv[1],O_RDONLY);
    } else {
        fprintf(stderr, "reading from stdin\n");
        readLn(0, O_RDONLY);

    }
}
