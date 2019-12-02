#include <stdio.h>
#include <stdlib.h>

void getNextFive(int x, int *result) {
  int arr[5];
  int i;
  for ( i=0;i<5;i++ ) {
      result[i] = x+i+1;
  }
}

int main (int argc, char** argv) {
    int x = 5;
    int arr[5];
    getNextFive(x, arr);
      int i;
      for ( i=0;i<5;i++ ) {
      fprintf(stdout,"Value of arr is: %d\n", arr[i]);
  }
   return EXIT_SUCCESS;
}
