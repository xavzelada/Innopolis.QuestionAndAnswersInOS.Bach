/* Please look at the comments in Overleaf document */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <time.h>
#include <sys/wait.h>

#define BUF_SIZE 16
/* NUM_OF_ITERS is an integer BUF_SIZE/4
since there are 2*NUM_OF_ITERS characters written by each of two processes */
#define NUM_OF_ITERS 4
#define SHM_KEY 0x1000
#define SEM_KEY 0x2000

struct shmseg {
    int complete;
    int buflen;
    char buf[BUF_SIZE];
};

// auxiliary method to fill the shared memory buffer
int fill_shmbuf(struct shmseg * shmp, char ch);

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
};

struct sembuf p = { 0, -1, SEM_UNDO};
struct sembuf v = { 0, +1, SEM_UNDO};

int main()
{
    // start time
    unsigned int strtm =  clock();

    int shmid;
    struct shmseg *shmp;

    // get the identifier of the System V shared memory segment associated with SHM_KEY
    shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
    if (shmid == -1) {
        perror("Error in shared memory");
        return 1;
    }

    // attach to the shared memory segment to get a pointer to it
    shmp = shmat(shmid, NULL, 0);
    if (shmp == (void *) -1) {
        perror("Error in shared memory attachment");
        return 1;
    }

    // initial buffer string length is 0
    shmp->buflen = 0;

    // get the System V semaphore set identifier associated with SEM_KEY
    int id = semget(SEM_KEY, 1, 0666 | IPC_CREAT);
    if(id < 0) {
        perror("Error in semget line");
        exit(11);
    }
    union semun u;
    u.val = 1;
    if(semctl(id, 0, SETVAL, u) < 0) {
        perror("Error in semctl line");
        exit(12);
    }

    int child_pid = fork();

    if(child_pid == 0) {
        // child process
        // child's character to append to the buffer
        char ch = 'C';
        for(int i = 0; i < NUM_OF_ITERS; i++)
        {
            // fill the buffer the 1st time
            if(semop(id, &p, 1) < 0) {
                perror("Error in the 1st semop p child line");
                exit(15);
            }
            shmp->buflen = fill_shmbuf(shmp, ch);
            shmp->complete = 0;
            sleep(rand() % 2);

            // fill the buffer the 2nd time
            if(semop(id, &v, 1) < 0) {
                perror("Error in the 2nd semop p child line");
                exit(16);
            }
            fill_shmbuf(shmp, ch);
            sleep(rand() % 2);
        }
        shmp->complete = 1;

        exit(0);
    }

    // parent process
    // equalize the task conditions with the message implementation
    sleep(1);
    // parent's character to append to the buffer
    char ch = 'P';
    for(int i = 0; i < NUM_OF_ITERS; i++)
    {
        // fill the buffer the 1st time
        if(semop(id, &p, 1) < 0) {
            perror("Error in the 1st semop p parent line");
            exit(15);
        }
        shmp->buflen = fill_shmbuf(shmp, ch);
        shmp->complete = 0;
        sleep(rand() % 2);

        // fill the buffer the 2nd time
        if(semop(id, &v, 1) < 0) {
            perror("Error in the 2nd semop p parent line");
            exit(16);
        }
        fill_shmbuf(shmp, ch);
        sleep(rand() % 2);
    }
    shmp->complete = 1;

    // the buffer operations are finished to this moment, we can measure the execution time
    unsigned int endtm = clock();
    unsigned int exectm = endtm - strtm;

    // wait for the child process to terminate to be sure message queue removal is safe
    waitpid(child_pid,NULL,0);
    // mark the segment to be destroyed
    shmctl(shmid,IPC_RMID,0);

    printf("Final message buffer is %s.\n", shmp->buf);
    printf("Execution time is %d clock ticks.\n", exectm);
}

int fill_shmbuf(struct shmseg * shmp, char ch) {
    int len = strlen(shmp->buf);
    shmp->buf[len] = ch;
    return len;
}