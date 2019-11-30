#include <stdio.h>
#include <stdlib.h>

#define STRSIZE 80
char string[STRSIZE];
//string = "test__";
char s1[] = "test1";
//char s2[] = "test2";

int strln(char string[]);
int strpos(char s1[],char s2[]);

int strln(char string[]) {
//  char *string;
  int i;
  for ( i=0;string[i] != '\0';i++ )
      ;
  return i;
}
int strpos(char s1[],char s2[]) {
  int len1;
  int len2;
  int i;
  int j1;
  int j2;

  len1 = strln(s1);
  len2 = strln(s2);
  for ( i=0;i+len2 <= len1;i++ ) {
      for ( j1=i,j2=0;j2 <= len2 && s1[j1] == s2[j2] ; j1++, j2++ ) {

        if ( j2 == len2 ) {
            return(i);
        }
        return(-1);

      }
  }

}

int main () {
   fprintf(stdout,"String length is: %d\n",strln("abracadabrdaasda"));

   return EXIT_SUCCESS;
}
