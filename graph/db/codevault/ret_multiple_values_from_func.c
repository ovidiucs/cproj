#include <stdio.h>
#include <stdlib.h>

void sumAndProduct(int a, int b, int* sum, int* prod){
  *sum = a + b;
  *prod = a * b;
}


int main (int argc, char** argv) {
    int x = 5;
    int y = 12;
    int sum = 0
    int prod = 0;
    sumAndProduct(x, y, &sum, &prod);
    fprintf(stdout,"The sum is %d and the product is %d\n", sum, prod);

   return EXIT_SUCCESS;
}
