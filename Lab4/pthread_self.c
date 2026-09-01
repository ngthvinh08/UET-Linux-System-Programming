#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Hàm mà thread sẽ chạy
void* myThread(void* arg) {
    // Lấy ID của chính thread này
    pthread_t tid = pthread_self();
    printf("Hello from thread! My ID is: %lu\n", (unsigned long)tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;

    // Tạo thread mới
    int rc = pthread_create(&tid, NULL, myThread, NULL);
    if (rc) {
        fprintf(stderr, "Error: pthread_create() failed with code %d\n", rc);
        exit(EXIT_FAILURE);
    }

    // Chờ thread kết thúc
    pthread_join(tid, NULL);

    printf("Main thread finished.\n");
    return 0;
}
