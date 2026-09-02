#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* worker(void* arg) {
    printf("Worker thread started\n");
    sleep(2);

    // Nếu gọi exit() ở đây → toàn bộ process chết
    // exit(0);

    // Nếu thay bằng pthread_exit(NULL); → chỉ thread này chết
    pthread_exit(NULL);

    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, worker, NULL);

    while (1) {
        printf("Main thread still running...\n");
        sleep(1);
    }
    return 0;
}
