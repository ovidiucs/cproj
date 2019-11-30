#include <stdio.h>
#include <stdlib.h>

#define STRSIZE 80
char string[STRSIZE] = "test__";
char s1[STRSIZE] = "100 test1";
char s2[STRSIZE] = "200 test2";

int strln(char str[]);
int strpos(char str1[],char str2[]);

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
  *	Return: integer, starting location of second string
  *****/

  int len1;
  int len2;
  int i;
  int j1;
  int j2;

  len1 = strln(str1);
  len2 = strln(str2);

  for ( i=0; i+len2 <= len1; i++ ) {
      for ( j1=i,j2=0;j2 <= len2 && s1[j1] == s2[j2] ; j1++, j2++ ) {
        if ( j2 == len2 ) {
            return(i);
        }
      }
    }
    return(-1);

}

int main () {
   fprintf(stdout,"String length is: %d\n",strln(string));
   fprintf(stdout,"String position is: %d\n",strpos(s1,s2));
   return EXIT_SUCCESS;
}
