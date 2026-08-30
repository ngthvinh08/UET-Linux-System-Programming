    /*
     * Bài tập: Viết chương trình C tạo tiến trình con với 2 trường hợp:
     * 1. Tiến trình cha không cần chờ tiến trình con kết thúc.
     * 2. Tiến trình cha phải chờ tiến trình con kết thúc rồi mới tiếp tục.
     */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {
        // Đây là tiến trình con
        printf("Child process is running...\n");
        sleep(2);
        printf("Child process finished.\n");
    } else {
        // Đây là tiến trình cha
        // Trường hợp 1: Cha không chờ con
        printf("Parent continues immediately without waiting.\n");

        // Trường hợp 2: Cha chờ con kết thúc
        wait(NULL);
        printf("Parent waited for child to finish.\n");
    }

    return 0;
}
