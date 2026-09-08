/*
- glob là shared resource mà cả hai thread cùng muốn tăng giá trị.
- my_mutex là mutex dùng để đảm bảo chỉ một thread được vào critical section tại một thời điểm.

Trong threadFunc, mỗi vòng lặp:
    - pthread_mutex_lock(&my_mutex) → thread xin quyền truy cập.
    - glob++ → thao tác trên biến toàn cục.
    - pthread_mutex_unlock(&my_mutex) → giải phóng quyền cho thread khác.

main tạo 2 thread, mỗi thread tăng glob 10 triệu lần. Nếu không có mutex, kết quả sẽ sai (do race condition). 
Với mutex, kết quả đúng là glob = 20000000.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int glob = 0;                          // biến toàn cục (shared resource)
static pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER; // mutex khởi tạo tĩnh

// Hàm chạy trong thread: tăng biến glob 'loops' lần
void *threadFunc(void *arg) {
    int loops = *((int *) arg);
    for (int j = 0; j < loops; j++) {
        pthread_mutex_lock(&my_mutex);   // vào critical section
        glob++;                     // cập nhật biến toàn cục
        pthread_mutex_unlock(&my_mutex); // ra khỏi critical section
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    int loops = 10000000;

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
    return 0;
}
