#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include "common.h"

#define BUFFER_SIZE 100
#define NUM_PRODUCERS 10
#define NUM_CONSUMERS 20

/* global */
int buffer[BUFFER_SIZE];
int pindex = 0;
int cindex = 0;
sem_t spaces;
sem_t items;
pthread_mutex_t mutex;

/* producer */
int produce(int id)
{
    int r = rand();
    printf("Producer %d produced %d\n", id, r);
    return r;
}

void *producer(void *param)
{
    int *id = (int*)param;
    for(int i = 0; i < 10000; i++)
    {
        int num = produce(id);
        sem_wait(&spaces);
        pthread_mutex_lock(&mutex);
        /* critical section */
        buffer[pindex] = num;
        pindex = (pindex + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&items);
    }
    free(param);
    pthread_exit(NULL);
}

/* consumer */
void consume(int id, int num)
{
    printf("Consumer %d consumed %d\n", id, num);
}

void *consumer(void *param)
{
    int *id = (int*)param;
    for(int i = 0; i < 10000; i++)
    {
        sem_wait(&items);
        pthread_mutex_lock(&mutex);
        /* critical section */
        int num = buffer[cindex];
        buffer[cindex] = -1;
        cindex = (cindex + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&spaces);
        consume(*id, num);
    }
    free(id);
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    /* semaphore & mutex */
    sem_init(&spaces, 0, BUFFER_SIZE);
    sem_init(&items, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_t threads[NUM_PRODUCERS+NUM_CONSUMERS];

    /* create producers */
    for(int i = 0; i < NUM_PRODUCERS; i++)
    {
        int *id = (int*)malloc(sizeof(int));
        *id = i;
        pthread_create(&threads[i], NULL, producer, id);
    }

    /* create consumers */
    for(int i = NUM_PRODUCERS; i < NUM_CONSUMERS; i++)
    {
        int *id = (int*)malloc(sizeof(int));
        *id = i-NUM_PRODUCERS;
        pthread_create(&threads[i], NULL, consumer, id);

    }

    /* join threads */
    for(int i = 0; i < NUM_PRODUCERS+NUM_CONSUMERS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    /* cleanup */
    sem_destroy(&spaces);
    sem_destroy(&items);
    pthread_mutex_destroy(&mutex);

    return 0;
}