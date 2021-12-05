/*
 * Murashko Artem B20-02
 * Exercise 3 OS Bach
 *
 * Task:
 *  Design an algorithm for CP (conditional P) along the lines of the algorithm for P.
 *
 * Solution:
 *  First, let's define what is CP. CP is a conditional P operation that decrements the
 *  value of the semaphore and returns an indication of true if its value is greater than 0.
 *  If the value of the semaphore is less than or equal to 0, the value of the semaphore is
 *  unchanged and the return value is false.
 *
 *  To implement CP along the lines of the algorithm for P we need to use the implementation
 *  of Pprim and Vprim algorithms given in Figure 12.7 that use atomic software instructions
 *  and semaphore lock component. Let us for simplicity assume, that the read_and_clear
 *  function is atomic instruction. For the CP algorithm, we should not fall asleep, so we do not
 *  need to use a sleep list. Initially, we need to execute the Pprim operation to ensure exclusive
 *  access to the semaphore and then decrements the semaphore value. If the value is greater
 *  than 0, we reset the semaphore lock with the Vprim operation and return TRUE. Otherwise, we
 *  increment the semaphore value, execute the Vprim operation and return FALSE.
 *
 *  Actually, we cannot properly simulate our CP operation due to non atomicity of read_and_clear
 *  instruction and due to inability to disable interrupts.
 */

#include <sys/mman.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

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

/*
 * Semaphore structure. Consists of a lock field to control
 * access to the semaphore, allowing only one process to
 * manipulate the other fields of the structure during P and V
 * operations. The value field determines whether a process
 * should have access to the critical region protected by the
 * semaphore.
 */
typedef struct {
    int* lock;
    int* value;
} Semaphore;

/*
 * Initialization of the semaphore.
 * The semaphore lock component must initialize to 1
 * to allow only one process to manipulate the other
 * fields of the structure during P and V operations.
 */
void INIT(Semaphore* semaphore) {
    semaphore->lock = create_shared_memory(1);
    *(semaphore->lock) = 1;
    semaphore->value = create_shared_memory(1);
    *(semaphore->value) = 1;
}

/*
 * Simulation of read_and_clear atomic instruction
 * for implementation of Pprim algorithm. When executing
 * the read and clear instruction, the machine reads the
 * value of a memory location, clears its value (sets it to 0),
 * and sets the condition code according to whether or not
 * the original value was zero. In our case TRUE if the original
 * value was zero and FAlSE otherwise.
 */
int read_and_clear(int* lock) {
    if (*lock == 0)
        return TRUE;

    *lock = 0;
    return FALSE;
}

/*
 * A process loops using the read and clear instruction,
 * until it reads a nonzero value.
 */
void Pprim(Semaphore* semaphore) {
    while(read_and_clear(semaphore->lock));
}

/*
 * Restore the value of the lock variable and allows
 * other processors to gain exclusive access to the resource.
 */
void Vprim(Semaphore* semaphore) {
    *(semaphore->lock) = 1;
}

/*
 * Conditional P operation. Ensure exclusive access to the
 * semaphore, decrement semaphore value and return TRUE if
 * it is greater than zero. Increment and return FALSE otherwise.
 */
int CP(Semaphore* semaphore) {
    /* actually, we must disable interrupts here */
    Pprim(semaphore);
    *(semaphore->value) -= 1; /* decrement instruction */
    if (*(semaphore->value) > 0) {
        Vprim(semaphore);
        /* we must enable interrupts here */
        return TRUE;
    }
    *(semaphore->value) += 1; /* increment instruction */
    Vprim(semaphore);
    /* we must enable interrupts here */
    return FALSE;
}


int main() {

    return 0;
}