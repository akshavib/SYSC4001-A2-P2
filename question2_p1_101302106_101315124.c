/*
* @file question2_p1.c
* @author 101302106 - Akshavi Baskaran 
* @author 101315124 - Liam Addie
*
* QUESTION 2 - Concurrent Processes in Unix
* Extended Processes Using exec() and Multiples of Three
*
* question2_p1.c: This program creates a child process using fork() 
* and then uses exec() to replace the child process with another program (question2_p2).
*/ 

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t pid; 

    /* fork the child process */
    pid = fork();

    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if (pid ==0){
        execlp("./question2_p2", "question2_p2", NULL); /* using exec function to launch process 2 */

    }
    else{
        int count = 0;
        while(1){
            if (count % 3 == 0){
                printf("Cycle number: %d - %d is a multiple of 3\n", count, count);
            }
            else{
                printf("Cycle number: %d\n", count);
            }
            count++;
            usleep(500000); /* a delay for 0.5s */
        }
    }
    return 0;
}