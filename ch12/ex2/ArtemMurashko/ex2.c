/*
 * Murashko Artem B20-02
 * Exercise 2 OS Bach
 *
 * Task:
 *  Use the shared memory system calls to test the C code for implementation of semaphores,
 *  shown in Figure 12.6. Several independent processes should execute P-V sequences on a semaphore.
 *
 * Solution:
 *  In this exercise we should demonstrate the work of semaphores without special machine
 *  instructions implemented by Dijkstra. Since processes have separate memory address
 *  space I was needed to use shared memory system calls. So implementation was slightly changed.
 *
 *  To test P-V sequences, I created a shared variable that acts as a variable to increment in a
 *  critical region. Each process should access a critical region and increment the variable by 1.
 *  So to make sure the algorithm works, the final value of the variable should be equal to the
 *  number of created processes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define NUMPROCS 5 /* number of processes */

/*
 * Returns shared memory buffer with
 * number of elements equal to length with
 * protection: readable and writable and
 * visibility: shared, but anonymous, i.e. only this process
 * and these children will be able to use it
 */
int* create_shared_memory(int length) {
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANONYMOUS;
    return mmap(NULL, sizeof(int) * length, protection, visibility, -1, 0);
}

typedef struct {
    int* val; /* lock entry for each process */
    int lastid; /* ID of last process to get semaphore */
} Semaphore;

int procid; /* process ID, unique per process */
int* lastid; /* ID of last process to get the semaphore */

/*
 * Initialize the semaphore. Set the lock entry of each
 * process equal to zero.
 */
void INIT(Semaphore* semaphore) {
    semaphore->val = create_shared_memory(NUMPROCS);
    lastid = create_shared_memory(1);
    for (int i = 0; i < NUMPROCS; i++)
        semaphore->val[i] = 0;
}

/*
 * Lock the semaphore by checking the values of the array val;
 * each process in the system controls one entry. When a process
 * locks a semaphore, it checks to see if other processes are currently
 * trying to lock it. If so process wait until the critical region
 * will be free.
 */
void Pprim(Semaphore* semaphore) {
    int i, first;
    loop:
        first = *lastid;
        semaphore->val[procid] = 1;
        forloop:
            for (i = first; i < NUMPROCS; i++) {
                if (i == procid) {
                    semaphore->val[i] = 2; /* our turn to use resource */

                    /*
                     * Check that the other process did not have time to enter the critical region.
                     * Wait again if it happened.
                     */
                    for (i = 0; i < NUMPROCS; i++)
                        if (i != procid && semaphore->val[i] == 2)
                            goto loop;

                    *lastid = procid;
                    return; /* now we can use the resource */
                } else if (semaphore->val[i])
                    goto loop;
            }
            first = 0;
            goto forloop;
}

/*
 * Free the semaphore and allow other processes to gain
 * exclusive access to the resource by clearing the entry
 * of the executing process in val and resetting lastid.
 */
void Vprim(Semaphore* semaphore) {
    *lastid = (procid + 1) % NUMPROCS; /* reset to next process */
    semaphore->val[procid] = 0;
}

int main() {
    Semaphore semaphore;
    INIT(&semaphore);

    int* shared_variable = create_shared_memory(1); /* variable to increment in a critical region */
    *lastid = 0; /* first process with id 0 will be the last process at the beginning */
    pid_t pid; /* id of a current process */

    for (int i = 0; i < NUMPROCS; ++i) {
        pid = fork();
        if (pid < 0) {
            printf("Fork Failed");
            exit(0);
        } else if (pid == 0) {
            procid = i;
            break;
        }
    }

    if (pid == 0) { /* child process */
        printf("Process %d try to enter critical region\n", procid);
        Pprim(&semaphore);
        printf("Process %d entered the critical region\n", procid);
        *shared_variable += 1;
//        sleep(1); /* uncomment to test different situation */
        printf("New value of the shared variable = %d\n", *shared_variable);
        Vprim(&semaphore);
        printf("Process %d exit the critical region\n", procid);
    } else if (pid > 0) { /* parent process */
        for (int i = 0; i < NUMPROCS; i++) /* wait for all child processes to be finished */
            waitpid(-1, NULL, 0);

        printf("Final value of the shared variable = %d, should be %d\n", *shared_variable, NUMPROCS);
        return 0;
    }
    return 0;
}