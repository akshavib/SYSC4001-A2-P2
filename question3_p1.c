/*
* QUESTION 3 - Concurrent Processes in Unix
* Using the wait() system call
*
* question3_p1.c: This program creates a child process using fork() 
* and then uses exec() to replace the child process with another program (question3_p2)
*/

#include <sys/types.h>
# include <sys/wait.h> /* for wait() system call */
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
        execlp("./question3_p2", "question3_p2", NULL); /* using exec function to launch process 2 */

    }
    else{
        wait(NULL); /* parent process waits for child to complete */
        printf("Child Complete, Parent Process ending now.\n");
    }
    return 0;
}