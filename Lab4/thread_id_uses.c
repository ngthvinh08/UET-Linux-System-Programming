#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

// Hàm thực thi của thread
void* worker(void* arg) {
    printf("Worker thread started, ID = %lu\n", pthread_self());
    sleep(3);
    printf("Worker thread finished\n");
    return NULL;
}

int main() {
    pthread_t tid;

    // Tạo thread mới
    pthread_create(&tid, NULL, worker, NULL);

    // 1. Thread management: dùng thread ID
    // a) pthread_join: chờ thread kết thúc
    printf("Main thread waiting for worker...\n");
    pthread_join(tid, NULL);

    // b) pthread_detach: tách thread (ví dụ tạo thread khác)
    pthread_t tid2;
    pthread_create(&tid2, NULL, worker, NULL);
    pthread_detach(tid2); // không cần join, hệ thống tự dọn dẹp

    // c) pthread_cancel: hủy thread
    pthread_t tid3;
    pthread_create(&tid3, NULL, worker, NULL);
    sleep(1);
    pthread_cancel(tid3); // gửi yêu cầu hủy thread

    // d) pthread_kill: gửi tín hiệu đến thread
    pthread_t tid4;
    pthread_create(&tid4, NULL, worker, NULL);
    sleep(1);
    pthread_kill(tid4, SIGUSR1); // gửi tín hiệu SIGUSR1

    // 2. Data structure tagging: gắn thread ID vào dữ liệu
    struct {
        pthread_t owner;
        int value;
    } resource;

    resource.owner = pthread_self(); // gắn ID của main thread
    resource.value = 123;

    // Kiểm tra thread nào sở hữu resource
    if (pthread_equal(resource.owner, pthread_self())) {
        printf("Main thread owns the resource (value=%d)\n", resource.value);
    }

    // 3. So sánh Thread IDs bằng pthread_equal
    if (pthread_equal(tid, pthread_self())) {
        printf("tid matches self\n");
    } else {
        printf("tid does not match self\n");
    }

    sleep(2); // chờ các thread khác in ra
    return 0;
}
