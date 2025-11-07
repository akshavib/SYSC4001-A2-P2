/*
* @file question4_p2.c
* @author 101302106 - Akshavi Baskaran 
* @author 101315124 - Liam Addie
*
* QUESTION 4 - Sharing memory between parent and child processes
* Using the memory mapping functions to share memory between a parent and child process.
*
* question4_p2.c: Executed by question4_p1.c using exec() and accesses shared memory
* to print cycle numbers in increasing order until 500 is reached.
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h> /* for memory mapping functions */
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>

typedef struct {
    int multiple; 
    int counter;
} sharedVars;

int main(int argc, char *argv[]){
    if (argc < 2){
        fprintf(stderr, "Missing Shared Memory ID Argument\n");
        return 1;
    }

    int shmid = atoi(argv[1]); /* get shared memory id from argument */

    sharedVars *shared = (sharedVars *) shmat(shmid, NULL, 0); /* attach shared memory segment to the parent */
    if (shared == (sharedVars *)-1) {
        perror("shmat failed");
        exit(1);
    }

    while (shared->counter <= 100){
        usleep(15000); /* a delay for 0.015s */
    }

    while (shared->counter <= 500){
        if (shared->counter % shared->multiple ==0){
            printf("_Process2_ || Cycle number: %d is a multiple of %d\n", shared->counter, shared->multiple);
        }
        else{
            printf("_Process2_ || Cycle number: %d\n", shared->counter); /* count is not a multiple of 3 */
        }
        usleep(25000); /* a delay for 0.05s */
    }
    printf("Shared counter > 500. Process 2 finished.\n");
    shmdt(shared); /* detach shared memory segment */
    return 0;
}