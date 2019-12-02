#include <stdio.h>
#include <stdlib.h>

int
*getNextFive(int x) {
  int *result = malloc(sizeof(int)*5);
  int i;
  for ( i=0;i<5;i++ ) {
      result[i] = x+i+1;
  }
  return result;
}

int main (int argc, char** argv) {
    int x = 5;

    int *arr = getNextFive(x);
      int i;
      for ( i=0;i<5;i++ ) {
      fprintf(stdout,"Value of arr is: %d\n", arr[i]);
  }
  free(arr);
   return EXIT_SUCCESS;
}
