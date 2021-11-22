#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include "unistd.h"
#include "time.h"
#define BUF_SIZE 10
#define SHM_KEY 75
#define KEY 15


void childProcess() {
    struct shmseg {
        long buf[BUF_SIZE];
    };
/*
    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short  *array;
    };*/
    struct sembuf p = { 0, -1, SEM_UNDO};
    struct sembuf v = { 0, +1, SEM_UNDO};
    int shmid;
    struct shmseg *shmp;
    shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
    shmp = shmat(shmid, NULL, 0);

    int id = semget(KEY, 1, 0666 | IPC_CREAT);
    //union semun u;
   // u.val = 1;
    //semctl(id, 0, SETVAL, u);
    semop(id, &p, 1);
    for (long i=0; i<BUF_SIZE; i++) {
        shmp->buf[i]=i+1;
        sleep(1);
    }
    //printf("Data is ready\n");
    semop(id, &v, 1);
    shmdt(shmp);
    shmctl(shmid, IPC_RMID, 0);
}

void parentProcess() {
    struct shmseg {
        long buf[BUF_SIZE];
    };
/*
    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short  *array;
    };*/
    struct sembuf p = { 0, -1, SEM_UNDO};
    struct sembuf v = { 0, +1, SEM_UNDO};
    int shmid;
    struct shmseg *shmp;
    shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
    shmp = shmat(shmid, NULL, 0);

    int id = semget(KEY, 1, 0666 | IPC_CREAT);
    //union semun u;
  //  u.val=semctl(id, 0, SETVAL, u);
    semop(id, &p, 1);
    for (long i=0; i<BUF_SIZE; i++) {
        printf("%ld ",shmp->buf[i]);
        //shmp->buf[i]=-1;
        //sleep(1);
    }
    semop(id, &v, 1);
    shmdt(shmp);
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
}