#include <pthread.h>
#include "common.h"

void *work(void *arg)
{
    char *a = (char*) arg;
    printf("provided %s\n", a);
    int *ret = malloc(sizeof(int));
    *ret = 252;
    pthread_exit(ret);
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        printf("Usage: ./threads.c arg \n");
        return 1;
    }

    pthread_t t;
    void *vr;

    pthread_create(&t, NULL, work, argv[1]);
    pthread_join(t, &vr);
    int *r = (int*) vr;
    printf("Thread returned %d\n", *r);
    free(vr);
    pthread_exit(0);
}