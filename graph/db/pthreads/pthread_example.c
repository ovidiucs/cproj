#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
// https://youtu.be/uA8X5zNOGw8
void *foo(void *arg){
  while(1) {
  fprintf(stdout,"My Turn\n");
  sleep(1);
  }
  return NULL;
}

void bar(){
  while(1) {
  fprintf(stdout,"Your Turn\n");
  sleep(1);
  }

}
int main (int argc, char** argv) {
  //1. Create thread.
  pthread_t newthread;

  //2. args, pthread_t address, NUL
  pthread_create(&newthread, NULL,foo, NULL);


//  foo();
   bar();
   return 0;
}
