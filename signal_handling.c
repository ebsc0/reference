#include <signal.h>
#include "common.h"

void sigint_handler(int sig)
{
    /* handle signal... ensure contains only reentrant functions ie. can be re-entered before completion and continue without side-effects */
}

int main()
{
    /*
     * void (*signal(int signal, void (*func)(int)))(int);
     */
    signal(SIGINT, sigint_handler); /* signal handle init */
    sleep(3);

    /*
    * int kill(int pid, int sig); send signal to pid process
    * int raise(itn sig); send signal to current process
    */
    return raise(SIGINT); /* raise SIGINT signal and return value */
}