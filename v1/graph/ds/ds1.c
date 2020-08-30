#include <stdio.h>
#include <stdlib.h>
#define NUMELTS 5
void aver() {
  int num[NUMELTS];     /***** Array of numbers *****/

  int i;
  int total;            /***** Sum of the numbers *****/

  float avg;            /***** Average of the numbers *****/

  intmax_t diff;           /***** diffenrece between each *****/
                        /***** number and te average  *****/

  total = 0;
  for ( i=0; i< NUMELTS ; i++ ) {
    /***** read the number in the array and add them *****/
    scanf("%d", &num[i]);
    total += num[i];
  } /*** end for ***/
  avg = total / NUMELTS;
  printf ("\nnumber difference"); /*** print heading ***/
  for ( i=0;i< NUMELTS;i++ ) {
      diff = num[i] - avg;
      printf("\n %d %.2f", num[i], diff);

  } /*** end for ***/
  printf("\naverage is: %.2f\n", avg); /*** end aver ***/

}
int main (int argc, char** argv) {

   aver ();
   return EXIT_SUCCESS;
}
