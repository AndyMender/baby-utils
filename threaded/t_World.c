/* This is a simple program to test POSIX threads (pthreads) in C. */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* Simple function to execute in a new thread */
void * helloWorldThreaded (void * argvp) {
  
  for ( int i = 0; i < 5; i++ ) {
	  printf ("Hello, World!\n");
	  sleep (10);
  }
  
  // return NULL; superficial
}

int main (void) {
  
  pthread_t thread_id; // thread pointer hook
  
  printf ("Prior to thread creation.\n");
  
  /* Create new thread and launch */
  pthread_create (&thread_id, NULL, helloWorldThreaded, NULL);
  
  /* Grab the output of the thread if it finishes */
  pthread_join (thread_id, NULL);
  
  printf ("After thread execution.\n");
  
  return EXIT_SUCCESS;
}
