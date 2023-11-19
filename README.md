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
||file|function(s)|description|
|---|---|---|---|
|0|common.h|rand_int|misc functions for general use|
|1|file_io.c|fopen, fclose, fprintf, fscanf|open/close files; read from file and write to file|
|2|fork.c|fork, wait|create a parent and child process and get their return values|
|3|signal_handling.c|signal, raise, kill|handle a signal when called|
|4|mailbox.c|msgget, msgsnd, msgrcv, msgctl|create mailbox and enqueue (send) and deque (recieve) messages between processes|
|5|socket_client.c, socket_server.c|socket, getaddrinfo, freeaddrinfo, connect, bind, listen, accept, close, send, recv|create a byte stream socket connection between client and server and send data between|
|6|curl.c|curl_global_init, curl_easy_init, curl_easy_setopt, curl_easy_perform, curl_easy_cleanup, curl_global_cleanup|use libcurl to get webpage|

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

### Consumer Producer Problem

### Breadth-First-Search

### Depth-First-Search

