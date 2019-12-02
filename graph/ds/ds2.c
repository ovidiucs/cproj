#include <stdio.h>
#include <stdlib.h>

#define STRSIZE 80
char string[STRSIZE] = "test__";
char s1[STRSIZE] = "0000010";
char s2[STRSIZE] = "010";

int strln(char str[]);
int strpos(char str1[],char str2[]);


int main () {
  fprintf(stdout,"String length is: %d\n",strln(string));
  fprintf(stdout,"String position is: %d\n",strpos(s1,s2));
  return EXIT_SUCCESS;
}


int
strln(char str[]) {
/*****
*	Takes a pointer to char string[] and
* calculates size of string without newline character
*****/

  int i = 0;
  while(str[i] != '\0'){
    i++;
  }
  return i;
}

int
strpos(char str1[],char str2[]) {
  /*****
  * Param: two strings
  *	Return: integer, starting location of
  * first occurence of the second parameters string withing the first parameter string
  *****/

  int len1 = 0;
  int len2 = 0;
  int i    = 0;
  int j1   = 0;
  int j2   = 0;

  len1 = strln(str1);
  len2 = strln(str2);
  printf("\nLen 1 is %d\tLen 2 is %d\n", len1, len2);
  for ( i=0;i+len2 <= len1; i++) {
      printf("\n i is %d\t  i+len2 is %d\t len1 is: %d\t\n", i,i+len2,len1);
      for ( j1=i,j2=0;(j2 <= len2) && (s1[j1] == s2[j2]); j1++, j2++ ) {
        printf("\n j1 is %d\t  j2 is %d\t s1[j1] == s2[j2] %d\t j2+len2 is %d\t len 2 is: %d\t\n", j1,j2,(s1[j1] == s2[j2]),j2+len2, len2);
        printf("\t\t\t\t s1[j1] is %c s2[j2] is %c\n", s1[j1],s2[j2]);
       if ( j2 == len2 ) {
          printf("\n j2 == len2 return %d\n\n\n", i);
            return(i);
        }
     //   printf("\n j1 is %d\t  j2 is %d\t len2 is \t %d\n", j1,j2, len2);
    }

  }
             return(-1);
}
