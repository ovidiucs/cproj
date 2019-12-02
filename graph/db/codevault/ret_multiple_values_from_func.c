#include <stdio.h>
#include <stdlib.h>

int sumAndProduct(int a, int b, int* sum, int* prod){
  if (sum == NULL || prod == NULL){
    return(0);
  }
  *sum = a + b;
  *prod = a * b;
}


int main (int argc, char** argv) {
    int x = 5;
    int y = 12;
    int sum = 0;
    int prod = 0;
    int status = sumAndProduct(x, y, &sum, &prod);
    if (!status) {
      fprintf(stderr, "Something went wrong\n");
    } else {
    fprintf(stdout,"The sum is %d and the product is %d\n", sum, prod);
    }
   return EXIT_SUCCESS;
}
