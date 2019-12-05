#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
// https://youtu.be/uA8X5zNOGw8
void *foo(void *arg){
  int *iptr = (int *) arg;
  for (int i = 0; i < 5; i++){
  fprintf(stdout,"My Turn and %d %d\n", i, *iptr);
  (*iptr)++;

  sleep(1);

  }
  return NULL;
}

void bar(){
  for (int i = 0; i < 2; i++){
  fprintf(stdout,"Your Turn\n");
  sleep(1);
  }

}
int main (int argc, char** argv) {
  int i = 5;
  //1. Create thread.
  pthread_t newthread;

  //2. args, pthread_t address, NUL
  pthread_create(&newthread, NULL,foo, &i);


//  foo();
   bar();
  pthread_join(newthread,NULL);
  fprintf(stdout,"Thread's done %d\n",i);
   return 0;
}
