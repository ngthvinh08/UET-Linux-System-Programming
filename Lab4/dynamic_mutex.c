#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int glob = 0;          // shared resource
static pthread_mutex_t my_mutex; // sẽ khởi tạo động

// Hàm chạy trong thread: tăng biến glob 'loops' lần
void *threadFunc(void *arg) {
    int loops = *((int *) arg);
    for (int j = 0; j < loops; j++) {
        pthread_mutex_lock(&my_mutex);   // vào critical section
        glob++;                          // cập nhật biến toàn cục
        pthread_mutex_unlock(&my_mutex); // ra khỏi critical section
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    int loops = 10000000;

    // Khởi tạo mutex động
    if (pthread_mutex_init(&my_mutex, NULL) != 0) {
        perror("pthread_mutex_init");
        exit(EXIT_FAILURE);
    }

    // Tạo 2 thread cùng chạy threadFunc
    if (pthread_create(&t1, NULL, threadFunc, &loops) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&t2, NULL, threadFunc, &loops) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // Chờ cả hai thread kết thúc
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // In kết quả cuối cùng
    printf("glob = %d\n", glob);

    // Hủy mutex khi không dùng nữa
    pthread_mutex_destroy(&my_mutex);

    return 0;
}
