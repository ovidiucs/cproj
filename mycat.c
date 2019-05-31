#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

//
static int readLn(char *fn, char *flags, char* mode){

}

int main(int argc, char** argv) {
    // check number of arguments

    if(argc > 2) {
        fprintf(stderr,"Usage: %s [filename]\n",argv[0]);
    } else if (argc == 2){
        fprintf(stderr, "Using file file");
        inputFd = open(argv[1],)
    } else {
        fprintf(stderr, "reading from stdin");
    }
}
