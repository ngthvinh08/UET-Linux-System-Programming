#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

// Handler cho các tín hiệu
void sigint_handler(int sig) {
    printf("Caught SIGINT (Ctrl+C)\n");
}

void sigsegv_handler(int sig) {
    printf("Caught SIGSEGV (Segmentation Fault)\n");
    exit(1); // thoát để tránh vòng lặp vô hạn
}

void sigalrm_handler(int sig) {
    printf("Caught SIGALRM (Timer expired)\n");
}

void sigchld_handler(int sig) {
    printf("Caught SIGCHLD (Child terminated)\n");
    // Thu hồi tiến trình con khi nó gọi exit() hoặc gây lỗi SIGSEGV
    // Thu hồi tiến trình con để tránh zombie
    int status;
    wait(&status);
}

int main() {
    // Đăng ký handler cho các tín hiệu
    signal(SIGINT, sigint_handler);
    signal(SIGSEGV, sigsegv_handler);
    signal(SIGALRM, sigalrm_handler);
    signal(SIGCHLD, sigchld_handler);

    pid_t pid = fork();
    if (pid == 0) {
        // Tiến trình con
        printf("Child process running...\n");
        sleep(2);

        // Gây lỗi segmentation fault để phát sinh SIGSEGV
        int *p = NULL; 
        *p = 42; // truy cập bộ nhớ không hợp lệ

        exit(0);
    } else {
        // Tiến trình cha
        printf("Parent process running...\n");

        // Đặt báo thức sau 3 giây → SIGALRM
        alarm(3);

        // Sau 5 giây, gửi SIGINT cho chính tiến trình cha
        sleep(5);
        kill(getpid(), SIGINT);

        // Sau 7 giây, gửi SIGKILL cho chính tiến trình cha
        sleep(2);
        kill(getpid(), SIGKILL);

        // Vòng lặp vô hạn để chờ tín hiệu
        while (1) {
            pause(); // chờ tín hiệu
        }
    }

    return 0;
}
