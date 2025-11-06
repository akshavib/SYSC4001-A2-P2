/*
* QUESTION 5 - Sharing memory and semaphores 
* Protect concurrent access to shared memory using semaphores
*
* question5_p1.c: Creates shared memory and spawns question5_p2
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
struct sembuf sbv = {0, 1, 0}; /* signal (V) */

int main(){
    int shmid = shmget(IPC_PRIVATE, sizeof(sharedVars), IPC_CREAT | 0666); /* create shared memory segment */
    if (shmid < 0) { 
        perror("shmget failed");
        exit(1);
    }

    sharedVars *shared = (sharedVars *) shmat(shmid, NULL, 0); /* attach shared memory segment to the parent */
    if (shared == (sharedVars *)-1) {
        perror("shmat failed");
        exit(1);
    }

    shared->multiple = 3; /* initialize the shared multiple */
    shared->counter = 0; /* initialize the shared counter */

    int semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666); /* creating semaphore */
    if (semid < 0) {
        perror("semget failed");
        exit(1);
    }

    semctl(semid, 0, SETVAL, 1); /* initialize semaphore to 1 */

    pid_t pid; 
    
    pid = fork(); /* fork the child process */

    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed\n");
        shmctl(shmid, IPC_RMID, NULL); /* removing the shared memory segment */
        semctl(semid, 0, IPC_RMID); /* removing the semaphore */
        return 1;
    }
    else if (pid == 0){
        char shm_id_str[16], sem_id_str[16];
        sprintf(shm_id_str, "%d", shmid); /* pass shmid as argument */
        sprintf(sem_id_str, "%d", semid); /* pass semid as argument */
        execlp("./question4_p2", "question4_p2", shm_id_str, sem_id_str, NULL); /* using exec function to launch process 2 */
    }
    else{
        while (shared->counter <= 500){
            semop(semid, &sbp, 1); /* wait (decrement) semaphore */
            if(shared->counter % shared->multiple == 0){ /* count is a multiple of 3 */
                printf("_Process1_ || Cycle number: %d is a multiple of %d\n", shared->counter, shared->multiple);
                shared->counter++;
            }
            else{
                printf("_Process1_ || Cycle number: %d\n", shared->counter); /* count is not a multiple of 3 */
            }
            shared->counter++;

            semop(semid, &sbv, 1); /* signal (unlock) */
            usleep(25000); /* delay 0.25s */
        }
        shmdt(shared); /* detach shared memory segment from parent */
        shmctl(shmid, IPC_RMID, NULL); /* removing the shared memory segment */

        wait(NULL); /* wait for child process to complete */
        printf("Shared counter > 500. Process 1 and Process 2 finished.\n");
    }
    return 0;
}
