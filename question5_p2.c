/*
* @file question5_p2.c
* @author 101302106 - Akshavi Baskaran 
* @author 101315124 - Liam Addie
*
* QUESTION 5 - Sharing memory and semaphores 
* Protect concurrent access to shared memory using semaphores
*
* question5_p2.c: Executed by question5_p1.c using exec() and accesses shared memory
* to print cycle numbers in increasing order until 500 is reached.
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h> /* for memory mapping functions */
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/stat.h>

typedef struct {
    int multiple; 
    int counter;
} sharedVars;

struct sembuf sbp = {0, -1, 0}; /* wait (P) */
struct sembuf sbv = {0, 1, 0};  /* signal (V) */

int main(int argc, char *argv[]){
    if (argc < 3){
        fprintf(stderr, "Missing Shared Memory ID Argument\n");
        return 1;
    }

    int shmid = atoi(argv[1]); /* get shared memory id from argument */
    int semid = atoi(argv[2]); /* get shared memory id from argument */

    sharedVars *shared = (sharedVars *) shmat(shmid, NULL, 0); /* attach shared memory segment to the parent */
    if (shared == (sharedVars *)-1) {
        perror("shmat failed");
        exit(1);
    }

    while (shared->counter <= 100){
        usleep(15000); /* a delay for 0.015s */
    }

    while (shared->counter <= 500){
        semop(semid, &sbp, 1); /* wait (P) */
        if (shared->counter % shared->multiple ==0){
            printf("_Process2_ || Cycle number: %d is a multiple of %d\n", shared->counter, shared->multiple);
        }
        else{
            printf("_Process2_ || Cycle number: %d\n", shared->counter); /* count is not a multiple of 3 */
        }
        semop(semid, &sbv, 1); /* signal (V) */
        usleep(25000); /* a delay for 0.05s */
    }
    printf("Shared counter > 500. Process 2 finished.\n");
    shmdt(shared); /* detach shared memory segment */
    return 0;
}