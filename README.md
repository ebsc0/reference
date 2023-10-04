# Reference

## Files
||file|function(s)|description|
|---|---|---|---|
|0|common.h|rand_int|misc functions for general use|
|1|file_io.c|fopen, fclose, fprintf, fscanf|open/close files; read from file and write to file|
|2|fork.c|fork, wait|create a parent and child process and get their return values|
|3|signal_handling.c|signal, raise, kill|handle a signal when called|
|4|mailbox.c|msgget, msgsnd, msgrcv, msgctl|create mailbox and enqueue (send) and deque (recieve) messages between processes|

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

## Consumer Producer Problem