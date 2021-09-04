#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex;

int a = 5, b = 7;

// Function to access the global data
void* add_two_numbers(void* arg)
{
    // Locking the semaphore
    sem_wait(&mutex);

    a = a + 3;
    b = b - 1;
    char *message;
    message = (char *)arg;
   
    printf("%s: a value is: %d and ", message, a);
    printf("b value is: %d\n", b);
   
    sleep(1);
    
    // Release/Signal the semaphore 
    sem_post(&mutex) ;
}

int main()
{   
    char *message1 = "Message 1";
    char *message2 = "Message 2";
    char *message3 = "Message 3";

    // initialize our semaphore
    // 1.) our first argument is the semaphore that we
    //     want to initialized (i.e mutex - mutually exclusive)
    // 2.) the second argument is the "shared" arg and because 
    //     it is 0, we are telling the semaphore that it is
    //     shared between threads.
    // 3.) the third argument is the value that we are assigning
    //     to the newly intialized semaphore.
    sem_init(&mutex, 0, 1);
   
    pthread_t t1, t2, t3;
   
    pthread_create(&t1, NULL, add_two_numbers, (void*)message1);
    sleep(1);
   
    pthread_create(&t2, NULL, add_two_numbers, (void*)message2);
    sleep(1);
   
    pthread_create(&t3, NULL, add_two_numbers, (void*)message3);
    sleep(1);
   
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
   
    // Destroy our semaphore
    sem_destroy(&mutex);
   
    return 0;
}
