#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//

int main(int argc, char** argv[]) {
    // check number of arguments
    if(argc < 2) {
        fprintf(stderr,"Usage: %s, [filename]",argv[1]);
    }
}