/*
* @file question1.c
* @author 101302106 - Akshavi Baskaran 
* @author 101315124 - Liam Addie
*
* QUESTION 1 - Concurrent Processes in Unix
* Running Two Processes: Parent and Child 
* 
* question1.c: This program creates a child process using fork system call
*/ 

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t pid; 

    /* fork the child process */
    pid = fork();

    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if (pid == 0) { /* child process */
        int count1 = 0;
        while(1){
            count1++;
            printf("Child PID: %d , Count: #%d\n", getpid(), count1);
            usleep(500000); /* a delay for 0.5s */
        }
    }
    else {
        int count2 = 0; /* parent process */
        while(1){
            count2++;
            printf("Parent PID: %d , Count: #%d\n", getpid(), count2); // ask if count should begin at 1 or if it can start at the huge number
            usleep(500000); /* a delay for 0.5s */
        }
    }
    return 0;
}