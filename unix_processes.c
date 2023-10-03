#include "common.h"

int process_a()
{
    printf("this is process a\n");
    return 0;
}

int process_b()
{
    printf("this is process b\n");
    return 0;
}

int main() 
{
    /* int return types for parent and child */
    int parent_status, child_status;

    /* create fork */
    pid_t pid = fork();

    if(pid < 0) /* check if fork was successful */
    {
        return 1;
    } 
    else if(pid == 0) /* child process */
    {
        printf("Child process: ");
        return process_a();
    }
    else /* parent process */
    {
        printf("Parent process: ");
        parent_status = process_b();
        /* wait on child process and assign its return value to child_status */
        wait(&child_status);
        /* get parent status and child status */
        printf("parent_status: %d, child_status: %d\n", parent_status, child_status);
    }

    return 0;
}