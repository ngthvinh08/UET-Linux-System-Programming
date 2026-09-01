#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <unistd.h>

// Custom signal handler function 
void handle_sigint(int sig) { 
    printf("\nReceived SIGINT (Ctrl+C). Ignoring it!\n"); 
} 

int main() { 
    // Associate SIGINT with the handler function 
    signal(SIGINT, handle_sigint); 
    while (1) { 
    printf("Running... Press Ctrl+C to test signal handling.\n"); 
    sleep(2); 
    } 
return 0;
} 