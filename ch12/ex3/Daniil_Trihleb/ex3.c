/**
 * @file ex3.c
 * @author d.trihleb
 * @date Nov 15, 2021
 * 
 * Task: 
 *      Design an algorithm for CP (conditional P) 
 *      along the lines of the algorithm for P.
 * 
 * Solution:
 *      As base for CP was used semaphore implementation
 *      from task 2 (Dijkstra [Dijkstra 65]). 
 *  
 * To compile the program use 
 *     gcc -Wall -pthread ex3.c -o ex3   
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

/* enum used as output for CP primitive */
typedef enum{
    FALSE,
    TRUE
} CP_return;


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

/* Implementation of CP operation. 
 * Represents already defined P operation,
 * but insted looping until getting resource
 * just check once and return result. 
 * 
 * @return 
 *      TRUE  - when resource free, process can start using it
 *      FALSE - resource busy
 */
CP_return CPprim(struct semaphore *sem){
        int i, first;

loop:
    first = *(sem->val + LAST_ID);
    *(sem->val + proc_id) = 1;
forloop:
    for (i = first; i < NUMPROCS; i++){
        if(i == proc_id){
            *(sem->val + i) = 2;
            for (i = 1 ; i < NUMPROCS; i++){
                if (i != proc_id && *(sem->val + i) == 2){
                    *(sem->val + proc_id) = 0;
                    return FALSE;
                }
            }
            *(sem->val + LAST_ID) = proc_id;
            return TRUE;
        } else if (*(sem->val + i)){
            *(sem->val + proc_id) = 0;
            return FALSE;
        }
    }
    first = 1;
    goto forloop; 
}

/* implementation of V operation */
void Vprim(struct semaphore *sem){
    *(sem->val + LAST_ID) = (proc_id + 1) % NUMPROCS;
    *(sem->val + proc_id) = 0;
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
        /* enter to the critical regeon 100 times */
        for (int i = 0; i < 2; i++){
            CP_return res;
            while ((res = CPprim(&Sem)) != TRUE);  /* loop until resource become free */
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
