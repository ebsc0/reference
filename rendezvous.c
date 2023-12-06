#include <semaphore.h>
#include <pthread.h>
#include "common.h"

sem_t aArrived;
sem_t bArrived;
sem_t cArrived;

void *work_a(void *arg)
{
    sleep((int) arg);
    printf("Thread A has arrived\n");

    /* rendezvous */
    sem_post(&aArrived);
    sem_wait(&bArrived);

    printf("Thread A has past rendezvous\n");
    pthread_exit(NULL);
}

void *work_b(void *arg)
{
    sleep((int) arg);
    printf("Thread B has arrived\n");

    /* rendezvous */
    sem_post(&bArrived);
    sem_wait(&aArrived);

    printf("Thread B has past rendezvous\n");
    pthread_exit(NULL);
}

// void *work_c(void *arg)
// {
    // sleep((int) arg);
    // printf("Thread C has arrived\n");

    // /* rendezvous*/
    // sem_post(&cArrived);
    // sem_post(&cArrived);
    // sem_wait(&aArrived);
    // sem_wait(&bArrived);

    // printf("Thread C has past rendezvous\n");
    // pthread_exit(NULL);
// }

int main(int argc, char **argv)
{
    /* initialize semaphores */
    sem_init(&aArrived, 0, 0);
    sem_init(&bArrived, 0, 0);
    
    /* create threads */
    pthread_t ta;
    pthread_t tb;
    pthread_t tc;

    pthread_create(&ta, NULL, work_a, 1);
    pthread_create(&tb, NULL, work_b, 5);

    /* join threads */
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);

    /* destroy semaphores */
    sem_destroy(&aArrived);
    sem_destroy(&bArrived);

    return 0;
}