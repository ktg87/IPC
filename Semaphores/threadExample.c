// This exmple shows how accessing global variables without a semaphore 
// can lead to inconsistency in the data.  All of the threads are
// trying to access the global variables at once and there is no
// proper locking used to prevent the variables from being used
// in a sporatic order.  So the print statements do not result
// as you would expect.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

// Global Data variables.
int a = 5, b = 7;

// Function that access the global data.
// This function acts as our critical section
void* add_two_numbers(void* arg)
{
   a = a + 3;
   b = b - 1;
   
   char *message;
   message = (char *)arg;

   printf("%s: a value is: %d and ", message, a);
   printf("b value is: %d\n", b);
   
   sleep(1);
   
   exit(0);
}

int main()
{
   // Creating the thread instances.
   // These three threads are sharing the same address space
   //
   pthread_t thread1, thread2, thread3;

   char *message1 = "Thread 1";
   char *message2 = "Thread 2";
   char *message3 = "Thread 3";
   
   //Syntax:
   // int pthread_create(pthread_t * thread,
   //                    const pthread_attr_t * attr,
   //                    void * (*start_routine)(void *),
   //                    void *arg);
   // Notes: each of the calls to pthread_create() have the 
   // following functionality:
   // 1.) thread<#> is the thread id that is returned by the create function
   // 2.) attr is NULL because we don't want to include any pthread_attr_t
   //     from <bits/pthreadtypes.h>
   // 3.) void * (*start_routine)(void *) is the pointer to the function 
   //     that is being threaded
   // 4.) arg is a message for each thread so we can see which message is 
   //     performing the calculation.
   pthread_create(&thread1, NULL, add_two_numbers, (void*)message1);
   pthread_create(&thread2, NULL, add_two_numbers, (void*)message2);
   pthread_create(&thread3, NULL, add_two_numbers, (void*)message3);

   // pthread_join() is waiting for its given thread to terminate
   // you can see the termination exit(0) in the add_two_numbers function
   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL);
   pthread_join(thread3, NULL);
   
   //Destroying the threads.
   pthread_exit(thread1);
   pthread_exit(thread2);
   pthread_exit(thread3);
   
   return 0;
}
