/*
* @file question2_p2.c
* @author 101302106 - Akshavi Baskaran 
* @author 101315124 - Liam Addie
*
* QUESTION 2 - Concurrent Processes in Unix
* Extended Processes Using exec() and Multiples of Three
*
* question2_p2.c: This program is executed by question2_p1.c using exec()
* and prints the cycle numbers in decreasing order.
*/ 

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    int count = 0;
    while(1){
        if (count % 3 == 0){
            printf("Cycle number: %d - %d is a multiple of 3\n", count, count);
        }
        else{
            printf("Cycle number: %d\n", count);
        }
        count--;
        usleep(500000); /* a delay for 0.5s */
    }
    return 0;
}
