#include <stdio.h>
#include "unistd.h"
#include <sys/ipc.h>
#include <sys/msg.h>
#include "time.h"
#define BUF_SIZE 10
#define MSGKEY 75

void childProcess() {
    struct msgform
    {
        long     mtype;
        long     mbuf[BUF_SIZE];
    }msg;
    int msgid = msgget(MSGKEY, 0666 | IPC_CREAT);
    msg.mtype = 1;
    for (long i=0; i<BUF_SIZE; i++) {
        msg.mbuf[i]=i+1;
        sleep(1);
    }
    //printf("Data is ready\n");
    //sleep(2);
    msgsnd(msgid, &msg, sizeof(msg), 0);
    msgctl(msgid, IPC_RMID, 0);
    /*
    for (long i=0; i<BUF_SIZE; i++) {
        msg.mbuf[i]=i+10;
        //sleep(1);
    }
    msgsnd(msgid, &msg, sizeof(msg), 0);*/
}

void parentProcess() {
    struct msgform
    {
        long     mtype;
        long     mbuf[BUF_SIZE];
    }msg;
    int msgid = msgget(MSGKEY, 0666 | IPC_CREAT);
    msgrcv(msgid, &msg, sizeof(msg), 1, 0);
    for (long i=0; i<BUF_SIZE; i++) {
        printf("%ld ",msg.mbuf[i]);
        //msg.mbuf[i]=-1;
        //sleep(2);
    }
/*
    msgrcv(msgid, &msg, sizeof(msg), 1, 0);/
    msgctl(msgid, IPC_RMID, 0);
    for (long i=0; i<BUF_SIZE; i++) {
        printf("%ld ",msg.mbuf[i]);
        msg.mbuf[i]=-1;
        //sleep(2);
    }
*/
}


int main() {
    unsigned int start_time =  clock();
    if (fork()==0) {
        //unsigned int start_time =  clock();
        childProcess();
        //unsigned int end_time = clock();
        //unsigned int work_time = end_time - start_time;
        //printf("\nChild Work Time : %d\n",work_time);
        return 0;
    } else {
        sleep(1);
        parentProcess();
    }
    unsigned int end_time = clock();
    unsigned int work_time = end_time - start_time;
    printf("\nWork Time : %d\n",work_time);
    return 0;
}
