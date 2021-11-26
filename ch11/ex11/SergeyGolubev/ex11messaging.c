/* Please look at the comments in Overleaf document */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <time.h>

#define BUF_SIZE 16
/* NUM_OF_ITERS is an integer BUF_SIZE/4
since there are 2*NUM_OF_ITERS characters written by each of two processes */
#define NUM_OF_ITERS 4
#define MSG_KEY1     75
#define MSG_KEY2     76

struct msgform
{
    long     mtype;
    char     mbuf[BUF_SIZE];
    int      buflen;
}msg;

// auxiliary method to fill the buffer (msg.mbuf)
void fill_mbuf(struct msgform * msgp, char ch);

int main()
{
    // start time
    unsigned int strtm =  clock();

    msg.mtype = 1;
    msg.buflen = 0;

    int child_pid = fork();

    if(child_pid == 0) {
        // child process
        // child's character to append to the buffer
        char ch = 'C';

        // get the System V message queue identifiers associated with MSG_KEY1 and MSG_KEY2
        int msgid1 = msgget(MSG_KEY1, 0666 | IPC_CREAT);
        int msgid2 = msgget(MSG_KEY2, 0666 | IPC_CREAT);

        // sending an initial message to allow Parent to write
        msgsnd(msgid1, &msg, sizeof(msg), 0);

        for(int i = 0; i < NUM_OF_ITERS; ++i)
        {
            //printf("C waits for msg from P.\n");
            msgrcv(msgid2, &msg, sizeof(msg), msg.mtype, 0);
            //printf("C received msg and begins to write.\n");

            // writing 2 characters to the buffer
            fill_mbuf(&msg, ch);
            //sleep(rand() % 2);
            fill_mbuf(&msg, ch);
            //sleep(rand() % 2);

            msgsnd(msgid1, &msg, sizeof(msg), 0);
            //printf("C sent msg to P.\n");
        }

        exit(0);
    }

    //parent process
    // parent's character to append to the buffer
    char ch = 'P';

    // sleep to let the child send the initial message
    sleep(1);

    // get the System V message queue identifiers associated with MSG_KEY1 and MSG_KEY2
    int msgid1 = msgget(MSG_KEY1, 0666 | IPC_CREAT);
    int msgid2 = msgget(MSG_KEY2, 0666 | IPC_CREAT);

    for(int i = 0; i < NUM_OF_ITERS; ++i)
    {
        //printf("P waits for msg from C.\n");
        msgrcv(msgid1, &msg, sizeof(msg), msg.mtype, 0);
        //printf("P received msg and begins to write.\n");

        // writing 2 characters to the buffer
        fill_mbuf(&msg, ch);
        //sleep(rand() % 2);
        fill_mbuf(&msg, ch);
        //sleep(rand() % 2);

        msgsnd(msgid2, &msg, sizeof(msg), 0);
        //printf("P sent msg to C\n");
    }

    // the buffer operations are finished to this moment, we can measure the execution time
    unsigned int endtm = clock();
    unsigned int exectm = endtm - strtm;

    // wait for the child process to terminate to be sure message queue removal is safe
    waitpid(child_pid,NULL,0);

    // remove the message queues
    msgctl(msgid1, IPC_RMID, 0);
    msgctl(msgid2, IPC_RMID, 0);

    printf("Final message buffer is %s.\n", msg.mbuf);
    printf("Execution time is %d clock ticks.\n", exectm);

    return 0;
}

void fill_mbuf(struct msgform * msgp, char ch) {
    msgp->mbuf[msgp->buflen] = ch;
    msgp->buflen++;
}