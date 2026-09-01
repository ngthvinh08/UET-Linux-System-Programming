#include <stdio.h> 
#include <unistd.h> 
#include <string.h> 
 
int main() { 
    int fd[2];  // File descriptors for pipe 
    char buffer[50]; 
 
    if (pipe(fd) == -1) { 
        perror("Pipe failed"); 
        return 1; 
    } 
 
    if (fork() == 0) {  // Child process (Consumer) 
        close(fd[1]);  // Close unused write end 
        read(fd[0], buffer, sizeof(buffer));  // Read from pipe 
        printf("Child received: %s\n", buffer); 
        close(fd[0]);  // Close read end 
    } else {  // Parent process (Producer) 
        close(fd[0]);  // Close unused read end 
        char message[] = "Hello from parent!"; 
        write(fd[1], message, strlen(message) + 1);  // Write to pipe 
        close(fd[1]);  // Close write end 
    } 
    return 0; 
}