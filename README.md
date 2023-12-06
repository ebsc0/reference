<div align="center">
<pre>
  ____  _____ _____ _____ ____  _____ _   _  ____ _____ 
 |  _ \| ____|  ___| ____|  _ \| ____| \ | |/ ___| ____|
 | |_) |  _| | |_  |  _| | |_) |  _| |  \| | |   |  _|  
 |  _ <| |___|  _| | |___|  _ <| |___| |\  | |___| |___ 
 |_| \_|_____|_|   |_____|_| \_|_____|_| \_|\____|_____|
</pre>
</div>
A source of common coding practices noted for reference.

## Sources
- [The Little Book of Semaphores](https://greenteapress.com/semaphores/LittleBookOfSemaphores.pdf)
- [UWaterloo ECE252 course playlist](https://www.youtube.com/playlist?list=PLFCH6yhq9yAHFaI00FrrgG0dPg8a5SjTJ)

## Files
||subject|file|function(s)|description|
|---|---|---|---|---|
|0|misc|common.h|rand_int|misc functions for general use|
|1|file IO|file_io.c|fopen, fclose, fprintf, fscanf|open/close files; read from file and write to file|
|2|processes|fork.c|fork, wait|create a parent and child process and get their return values|
|3|signals|signal_handling.c|signal, raise, kill|handle a signal when called|
|4|mailbox|mailbox.c|msgget, msgsnd, msgrcv, msgctl|create mailbox and enqueue (send) and deque (recieve) messages between processes|
|5|sockets|socket_client.c, socket_server.c|socket, getaddrinfo, freeaddrinfo, connect, bind, listen, accept, close, send, recv|create a byte stream socket connection between client and server and send data between|
|6|cURL|curl.c|curl_global_init, curl_easy_init, curl_easy_setopt, curl_easy_perform, curl_easy_cleanup, curl_global_cleanup|use libcurl to get webpage|
|7|pipes|pipes.c|
|8|threads|threads.c|
|9|synchronization patterns|mutex.c, rendevouz.c, 

## Notes

### POSIX signals
|signal|value|action|comment|
|---|---|---|---|
|SIGHUP|1|terminate|Hangup detected on controlling terminal or death of controlling process|
|SIGINT|2|terminate|Interrupt from keyboard|
|SIGQUIT|3|terminate and core dump|Quit from keyboard|
|SIGILL|4|terminate and core dump|Illegal Instruction|
|SIGABRT|6|terminate and core dump|Abort signal from abort(3)|
|SIGFPE|8|terminate and core dump|Floating point exception|
|SIGKILL|9|terminate|Kill signal|
|SIGSEGV|11|terminate and core dump|Invalid memory reference|
|SIGPIPE|13|terminate|Broken pipe: write to pipe with no readers|
|SIGALRM|14|terminate|Timer signal from alarm(2)|
|SIGTERM|15|terminate|Termination signal|
|SIGUSR1|30,10,16|terminate|User-defined signal 1|
|SIGUSR2|31,12,17|terminate|User-defined signal 2|
|SIGCHLD|20,17,18|ignore|Child stopped or terminated|
|SIGCONT|19,18,25|continue|Continue if stopped|
|SIGSTOP|17,19,23|stop|Stop process|
|SIGTSTP|18,20,24|stop|Stop typed at terminal|
|SIGTTIN|21,21,26|stop|terminateinal input for background process|
|SIGTTOU|22,22,27|stop|terminateinal output for background process|

### Sockets
```c
int socket(int domain, int type, int protocol)
```
- domain: address format ex: AF_INET (IPv4)
- type: type of data ex: SOCK_DGRAM (message; unidirectional) or SOCK_STREAM (byte stream; bidirectional)
- protocol: how data is transported ex: 0 (TCP/IP; default)

### Endianness
![endianness](https://upload.wikimedia.org/wikipedia/commons/thumb/5/5d/32bit-Endianess.svg/800px-32bit-Endianess.svg.png)

#### Big-Endian
Most significant byte is at the lowest memory address and the least significant byte at the largest memory address

#### Little-Endian
Most significant byte is at the largest memory address and the least significant byte at the lowest memory address

#### Host-Network Endian Translation Functions
```c
#include <arpa/inet.h>

uint32_t htonl(uint32_t hostint32) /* translate 4 byte int to network format */
uint16_t htons(uint16_t hostint16) /* translate 2 byte int to network format */
uint32_t ntohl(uint32_t netint32) /* translate 4 byte int to host format */
uint16_t ntohs(uint16_t netint16) /* translate 2 byte int to host format */
```

### cURL
[cURL](https://curl.se/libcurl/) is a client-side URL transfer library.

#### Boilerplate
```c
/* 1. instantiate cURL handler */
CURL *curl; 

/* 2. initialize curl global */
curl_global_init(CURL_GLOBAL_DEFAULT);

/* 3. initialize curl easy */
curl = curl_easy_init(); 

/* 4. use setopt to set url */
curl_easy_setopt(curl, CURLOPT_URL, "https://curl.se/libcurl/");

/* 5. perform request */
res = curl_easy_perform(curl);

/* 6. cleanup easy */
curl_easy_cleanup(curl); 

/* 7. cleanup global */
curl_global_cleanup(); 
```

### Pipes

### Threads
```c
#include <pthreads.h>
int pthread_create(pthread_t *thread, const phread_attr_t *attr, void *(*start_routine)(void *), void *argument);
void pthread_exit(void *retval);
int pthread_join(pthread_t *thread, void **retval);
int pthread_setcanceltype(int type, int *oldtype); /* PTHREAD_CANCEL_DEFERRED (default); PTHREAD_CANCEL_ASYNCHRONOUS */
int pthread_testcancel(void);
void pthread_cleanup_push(void (*routine)(void*), void *argument)
void pthread_cleanup_pop(int execute)
```

### Synchronization Patterns
A computer may have mutliple processes or threads executing concurrently (two events are concurrent if we cannot tell by looking at the program which will happen first). However, this may present a challenge when dealing with shared variables where two writers are writing to a variable or a reader and a writer access the same variable - The outcomes of every execution is non-deterministic.

To solve this issue, we use semaphores to restrict access of a critical section to a number of processes or threads.

#### Semaphores
A semaphore is an integer that can be incremented or decremented only:
1. When a thread decrements a semaphore, if the result is negative, the thread blocks itself and cannot continue until another thread increments the semaphore.
2. When a thread increments the semaphore, if there are other threads waiting, one of the waiting threads gets unblocked.

```c
#include <semaphore.h>
int sem_init(sem_t *semaphore, int shared, int init_value); /* shared = 0 (threads); shared = 1 (processes) */
int sem_destroy(sem_t *semaphore);
int sem_wait(sem_t *semaphore);
int sem_post(sem_t *semaphore);
```

#### Mutual Exclusion
Allow only one thread to be in the critical section at a time.

#### Rendevouz
Multiple threads arrive at a point of execution and no thread is allowed to continue until all threads have arrived.

#### Barrier

### Consumer-Producer Problem


### Reader-Writer Problem

### Breadth-First-Search

### Depth-First-Search

