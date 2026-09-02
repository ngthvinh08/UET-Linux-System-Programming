/*
 * Giải thích về condition variable:
 *
 * - Mỗi thread khi gọi pthread_cond_wait(&cond, &mutex)
 *   sẽ tự động đăng ký vào hàng đợi chờ của condition variable đó.
 *
 * - Khi một thread khác gọi pthread_cond_signal(&cond),
 *   hệ thống sẽ chọn ít nhất một thread trong hàng chờ để đánh thức.
 *
 * - Khi gọi pthread_cond_broadcast(&cond),
 *   hệ thống sẽ đánh thức tất cả thread đang nằm trong hàng chờ
 *   của condition variable đó.
 *
 *    Vì vậy, controller không cần biết có bao nhiêu worker.
 *    Nó chỉ việc gọi signal hoặc broadcast, kernel sẽ lo việc
 *    đánh thức đúng các thread đang chờ trên biến cond.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int ready = 0; // trạng thái chung

void* worker(void* arg) {
    long id = (long)arg;
    pthread_mutex_lock(&mutex);
    while (!ready) {
        // tất cả worker sẽ chờ ở đây
        pthread_cond_wait(&cond, &mutex);
    }
    pthread_mutex_unlock(&mutex);

    printf("Worker %ld: được đánh thức và bắt đầu làm việc!\n", id);
    return NULL;
}

void* controller(void* arg) {
    sleep(2); // giả sử chuẩn bị dữ liệu mất thời gian
    pthread_mutex_lock(&mutex);
    ready = 1;
    printf("Controller: dữ liệu đã sẵn sàng, broadcast cho tất cả worker!\n");

    // đánh thức tất cả worker đang chờ
    pthread_cond_broadcast(&cond);

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t workers[3], ctrl;

    // tạo 3 worker
    for (long i = 0; i < 3; i++) {
        pthread_create(&workers[i], NULL, worker, (void*)i);
    }

    // tạo controller
    pthread_create(&ctrl, NULL, controller, NULL);

    // join tất cả
    for (int i = 0; i < 3; i++) {
        pthread_join(workers[i], NULL);
    }
    pthread_join(ctrl, NULL);

    return 0;
}
