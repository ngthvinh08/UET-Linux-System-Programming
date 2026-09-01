#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Hàm mà thread sẽ chạy
void* myThread(void* arg) {
    printf("Hello from the new thread!\n");
    pthread_exit(NULL); // kết thúc thread
}

int main() {
    pthread_t tid;  // ID của thread

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
