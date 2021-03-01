#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *increment();
void *decrement();

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int counter = 0;

int
main()
{
     pthread_t thread1, thread2;
     char *message1 = "Thread 1";
     char *message2 = "Thread 2";
     int  iret1, iret2;
     
    /* Create independent threads each of which will execute function */

     iret1 = pthread_create( &thread1, NULL, increment, NULL);
     iret2 = pthread_create( &thread2, NULL, decrement, NULL);

     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */

     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL); 

     printf("Thread 1 returns: %d\n",iret1);
     printf("Thread 2 returns: %d\n",iret2);

     printf("Counter = %d\n", counter);
     return 0;
}

void *increment() {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 10000; i++) {
        counter = counter + 1;
    }
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}

void *decrement() {
    pthread_cond_wait(&cond, &mutex);
    for (int i = 0; i < 10000; i++) {
        counter = counter - 1;
    }
    pthread_mutex_unlock(&mutex);
}