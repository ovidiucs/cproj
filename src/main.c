#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../lib/sds/sds.h"
#include "../include/square.h"


int main (int argc, char** argv) {
    if (argc != 2) {
      fprintf(stderr,"Argument count missing\n");
    }
    fprintf(stdout, "The number of arguments is: %d\n",argc);
    fprintf(stdout, "%s\n","correct" ); 

    int rc = square(4,5);
    fprintf(stdout, "%d\n",rc);
    return EXIT_SUCCESS;
}
