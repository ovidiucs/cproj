#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "sds/sds.h"




int main (int argc, char** argv) {
    if (argc != 2) {
      fprintf(stderr,"Argument count missing\n");
    }
    fprintf(stdout, "The number of arguments is: %d\n",argc);
    fprintf(stdout, "%s\n","correct" ); 

    return EXIT_SUCCESS;
}
