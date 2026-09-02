/*
 * System calls / API được dùng:
 * - pthread_create(): tạo một thread mới trong cùng process.
 * - pthread_mutex_lock() / pthread_mutex_unlock(): khóa/mở khóa mutex để đồng bộ truy cập biến dùng chung.
 * - pthread_cond_wait(): cho thread chờ trên condition variable, tạm nhả mutex trong lúc chờ.
 * - pthread_cond_signal(): báo hiệu (wake up) một thread đang chờ trên condition variable.
 * - pthread_join(): (không dùng trong ví dụ này) thường để chờ thread kết thúc và thu hồi tài nguyên.
 *
 * Ý nghĩa:
 * - Condition variable kết hợp với mutex giúp các thread giao tiếp bằng tín hiệu,
 *   tránh việc phải kiểm tra liên tục (busy waiting).
 * - Trong ví dụ, thread worker sau khi hoàn thành công việc sẽ signal cho main biết.
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond  = PTHREAD_COND_INITIALIZER;
int done = 0;   // cờ báo hiệu thread đã xong

void* worker(void* arg) {
    printf("Thread đang chạy...\n");

    // Giả sử làm việc xong
    pthread_mutex_lock(&lock);
    done = 1;  // đánh dấu đã hoàn thành
    pthread_cond_signal(&cond); // báo hiệu cho thread khác
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, worker, NULL);

    // Thay vì join (blocking), ta kiểm tra bằng condition variable
    pthread_mutex_lock(&lock);
    while (!done) {
        // chờ tín hiệu từ worker
        pthread_cond_wait(&cond, &lock);
    }
    pthread_mutex_unlock(&lock);

    printf("Main biết thread đã xong!\n");
    return 0;
}
