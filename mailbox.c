#include <sys/msg.h>
#include <sys/ipc.h>
#include "common.h"

/* message struct */
typedef struct {
    long mtype;
    float data;
    char *string;
} message;

int main()
{
    /* create mailbox queue */
    int mailbox_id = msgget(IPC_PRIVATE, 0666 | IPC_CREAT); /* 6 = (octal) 110 -> 0666 = 0110110110 -> read/write permissions for user, group, everyone */

    /* fork */
    pid_t pid = fork();
    if(pid < 0) /* fork error */
    {
        return -1;
    }
    else if(pid > 0) /* parent process */
    {
        message msg1;
        msg1.mtype = 10;
        msg1.data = 3.14;
        msg1.string = "hello world";

        /* send message to mailbox */
        msgsnd(mailbox_id, &msg1, sizeof(message), 0);
        printf("sent message to mailbox\n");
    }
    else /* child process */
    {
        message msg2;

        /* recieve message from mailbox */
        msgrcv(mailbox_id, &msg2, sizeof(message), 10, 0);
        printf("recieved message from mailbox: data = %f, string = %s\n", msg2.data, msg2.string);

        /* delete mailbox */
        msgctl(mailbox_id, IPC_RMID, NULL); /* we cannot remove mailbox outside child (reciever) since mailbox needs to stay alive until child recieved message! */
        printf("mailbox removed\n");
    }
    return 0; 
}
