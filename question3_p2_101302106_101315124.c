/*
* @file question3_p2.c
* @author 101302106 - Akshavi Baskaran 
* @author 101315124 - Liam Addie
*
* QUESTION 3 - Concurrent Processes in Unix
* Using the wait() system call
*
* question3_p2.c: This program is executed by question3_p1.c using exec()
* and prints the cycle numbers in decreasing order until -500 is reached.
*/ 

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    int count = 0;
    while(count >= -500){
        if (count % 3 == 0){
            printf("Cycle number: %d - %d is a multiple of 3\n", count, count);
        }
        else{
            printf("Cycle number: %d\n", count);
        }
        count--;
        usleep(10000); /* a delay for 0.01s */
    }
    printf("Child Process Complete.\n");
    return 0;
}