#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Hàm thực thi của thread
void* worker(void* arg) {
    printf("Worker thread started\n");
    sleep(5); // giả lập công việc mất thời gian
    printf("Worker thread finished\n");
    return NULL;
}

int main() {
    pthread_t tid;

    // Tạo thread
    pthread_create(&tid, NULL, worker, NULL);

    printf("Main thread waiting for worker...\n");

    // Đợi thread kết thúc
    // Comment dòng này để thấy sự khác nhau
    pthread_join(tid, NULL);

    printf("Main thread continues after worker finished\n");
    return 0;
}
