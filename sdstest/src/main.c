#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "sds/sds.h"
#include "square.h"


int main (int argc, char** argv) {

    int rc = 0;

    if (argc == 2) {
      fprintf(stderr,"Argument count missing\n");
     } else if (argc == 1) {
       fprintf(stderr,"Reading from stdin\n");
     } else {
       fprintf(stderr,"Usage: %s text [file...]\n", argv[0]);
     }
    
    sds mystring = sdsnew("Hello World!");
    fprintf(stdout, "The sds string is %s\n",mystring ); 
    fprintf(stdout, "The sds length string is %d\n", (int) sdslen(mystring) ); 
    sds mynewstring = sdsgrowzero(mystring,3000);
    fprintf(stdout, "The sds length string is %s\n", mynewstring ); 
    fprintf(stdout, "The sds length string is %d\n", (size_t) sdslen(mynewstring) ); 
    sdsfree(mystring);
    sdsfree(mynewstring);

    rc = square(4,5);
//    fprintf(stdout, "%d\n",rc);
    return EXIT_SUCCESS;
}
