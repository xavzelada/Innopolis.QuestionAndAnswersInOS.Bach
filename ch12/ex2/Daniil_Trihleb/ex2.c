/**
 * @file ex2.c
 * @author d.trihleb
 * @date Nov 15, 2021
 * 
 * Task: 
 *      Implement Dijkstra [Dijkstra 65] semaphores and
 *      check them with usage of shared memory
 * 
 * Solution:
 *      Shared memory created by command mmap().
 *      Shared memory structure:
 *        0 - NUMPROCS:  each cell belongs to particular process
 *        NUMPROCS:      counter for process intersection spotting
 *        NUMPROCS + 1:  last ID of process that access critical region
 *        NUMPROCS + 2:  itersection counter
 *      
 *      Introduces changes to  [Dijkstra 65] implementation:
 *        - lastID is present in shared memory (insted of global variable)
 *        - structure "semaphore" contains pointer to the beginning of shared memory
 *          insted of array
 *
 *      Algorithm for spotting process intersection:
 *        - process trying access critical region
 *        - when critical region free enter it and check if COUNTER != 0
 *        - id COUNTER != 0 increment INTERSECTION_COUNTER by 1
 *        - increment COUNTER
 *        - do job in critical egeon
 *        - decrement COUNTER 
 *
 *
 *      To build program use 
 *          gcc -Wall -pthread ex2.c -o ex2
 */



#include <stdio.h>          /* printf()                       */
#include <stdlib.h>         /* exit()                         */
#include <sys/types.h>      /* pid_t                          */
#include <fcntl.h>          /* O_CREATE, O_EXEC               */
#include <errno.h>          /* errno                          */
#include <unistd.h>         /* sleep(), usleep()              */
#include <sys/wait.h>       /* sem_wait()                     */
#include <sys/mman.h>       /* mman(), munman()               */

#define NUMPROCS            10
#define SHARED_SIZE         (NUMPROCS + 3)
#define COUNTER             (NUMPROCS)
#define LAST_ID             (NUMPROCS + 1)
#define INTERSECTION        (NUMPROCS + 2)

/* struct representing semaphore */ 
struct semaphore{
    int* val;
    int last_id;
};

pid_t proc_id;      /* current process id           */ 
pid_t last_id = 0;  /* last semaphore access proc id*/

/* function for semaphore implementation */
void INIT(struct semaphore *sem){ 
    for (int i = 0; i < SHARED_SIZE; i++)
        *(sem->val + i) = 0;
}

/* implementation of P operation */
void Pprim(struct semaphore *sem){
    int i, first;

loop:
    first = *(sem->val + LAST_ID);
    *(sem->val + proc_id) = 1;
forloop:
    for (i = first; i < NUMPROCS; i++){
        if(i == proc_id){
            *(sem->val + i) = 2;
            for (i = 1 ; i < NUMPROCS; i++)
                if (i != proc_id && *(sem->val + i) == 2)
                    goto loop;
            
            *(sem->val + LAST_ID) = proc_id;
            return;
        } else if (*(sem->val + i)){
            goto loop;
        }
    }
    first = 1;
    goto forloop;        
}

/* implementation of V operation */
void Vprim(struct semaphore *sem){
    *(sem->val + LAST_ID) = (proc_id + 1) % NUMPROCS;
    *(sem->val + proc_id) = 0;
    //printf("Process %d, last_id: %d\n", proc_id,  *(sem->val + LAST_ID));
}

int main (int argc, char **argv){
    /* process id */
    pid_t pid;                        

    /* initialization of shared memory segment */ 
    int *shared = (int*) mmap (NULL,                        /* starting address */
                                sizeof(int)*SHARED_SIZE,    /* required size    */
                                PROT_READ  | PROT_WRITE,    /* protection       */
                                MAP_SHARED | MAP_ANON,      /* flag             */
                                -1,                         /* filedes          */
                                0);                         /* offset           */

    struct semaphore Sem;
    Sem.val = shared; 

    INIT(&Sem);        

    /* create child processes */
    for (int processNumber = 0; processNumber < NUMPROCS; processNumber++){
        pid = fork();
        /* check if error occur */
        if (pid < 0){
            /* release semaphore */ 
            munmap(shared, sizeof(int)*SHARED_SIZE);
            printf("Fork error occur");
            exit(0);
        } else if (pid == 0){
            proc_id = processNumber;
            break;               /* child process */
        }
    }

    /* parent process */ 
    if(pid != 0){
        /* wait for children finish execution */
        while (pid = waitpid(-1, NULL, 0)){
            if (errno == ECHILD){
                break;
            }
        }

        printf("\nParrent process:  All child processes are finished \n");

        printf("\nProcess intersection detected %d times\n", *(Sem.val + INTERSECTION));

        /* release semaphore */ 
        munmap(shared, sizeof(int)*SHARED_SIZE);

        /* safe exit */
        exit(0);
    }

    /*  child process */
    else{
        /* enter to the critical regeon 10 times */
        for (int i = 0; i < 10; i++){
            Pprim(&Sem);
            //printf("Child Proc %d entered\n", proc_id);
            if(*(shared + COUNTER) != 0){
                *(shared + INTERSECTION) += 1;
            }
            *(shared + COUNTER) += 1;
            for(int temp = 0; temp < 100; temp++);
            *(shared + COUNTER) -= 1;
            Vprim(&Sem);
        }
        exit(0);
    }
}
