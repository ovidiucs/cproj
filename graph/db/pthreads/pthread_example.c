#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void foo(){
  while(1) {
  fprintf(stdout,"My Turn\n");
  sleep(1);
  }
}

void bar(){
  while(1) {
  fprintf(stdout,"Yout Turn\n");
  sleep(1);
  }

}
int main (int argc, char** argv) {

    foo();
    bar();
   return 0;
}
