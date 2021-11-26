#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include "unistd.h"
#include "time.h"
#define BUF_SIZE 3
#define SHM_KEY 75
#define KEY 15


void childProcess() {
    struct shmseg {
        long buf[BUF_SIZE];
    };
    struct sembuf p = { 0, -1, SEM_UNDO};
    struct sembuf v = { 0, +1, SEM_UNDO};
    int shmid;
    struct shmseg *shmp;
    shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
    shmp = shmat(shmid, NULL, 0);

    int id = semget(KEY, 1, 0666 | IPC_CREAT);
    semop(id, &p, 1);
    for (long i=0; i<BUF_SIZE; i++) {
        shmp->buf[i]=i+1;
        sleep(1);
    }
    //Data is ready;
    semop(id, &v, 1);
    shmdt(shmp);
    shmctl(shmid, IPC_RMID, 0);
}

void parentProcess() {
    struct shmseg {
        long buf[BUF_SIZE];
    };
    struct sembuf p = { 0, -1, SEM_UNDO};
    struct sembuf v = { 0, +1, SEM_UNDO};
    int shmid= shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
    struct shmseg *shmp= shmat(shmid, NULL, 0);
    int id = semget(KEY, 1, 0666 | IPC_CREAT);
    semop(id, &p, 1);
    for (long i=0; i<BUF_SIZE; i++) {
        printf("%ld ",shmp->buf[i]);
    }
    semop(id, &v, 1);
    shmdt(shmp);
}


int main() {
    unsigned int work_time=0;
    unsigned int start_time =  clock();
    if (fork()==0) {
        childProcess();
        return 0;
    } else {
        sleep(1);
        parentProcess();
    }
    unsigned int end_time = clock();
    work_time += end_time - start_time;
    printf("\nWork Time : %d\n",work_time);
}
