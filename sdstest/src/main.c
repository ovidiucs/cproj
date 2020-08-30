#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "sds/sds.h"
#include "square.h"


int main (int argc, char** argv) {
    if (argc != 2) {
      fprintf(stderr,"Argument count missing\n");
    }
    
 sds mystring = sdsnew("Hello World!");
//    printf("%s\n", mystring);
//    sdsfree(mystring);

    fprintf(stdout, "The number of arguments is: %d\n",argc);
    fprintf(stdout, "The sds string is %s\n","test" ); 

    int rc = square(4,5);
    fprintf(stdout, "%d\n",rc);
    return EXIT_SUCCESS;
}
