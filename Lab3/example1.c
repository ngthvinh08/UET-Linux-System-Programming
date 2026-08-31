#include <stdio.h> 
#include <unistd.h>
#include <sys/wait.h>

void main() 
{ 
pid_t childPid;    /* Used in parent after successful fork() to record PID of child */ 
    switch (childPid = fork()) { 
        case -1:                  
            /* fork() failed */ 
            printf("Error when creating child process");/* Handle error */ 
        case 0:                  
            printf("I am child process");     
        default:
            printf("I'm the parent process");                  
    } 
}