/***************************************************************************************************
Giải thích:
    - Producer thêm dữ liệu vào buffer, nếu đầy thì chờ.
    - Consumer lấy dữ liệu từ buffer, nếu rỗng thì chờ.
    - Khi producer thêm dữ liệu, nó gọi pthread_cond_signal(&cond) để đánh thức ít nhất một consumer đang chờ.
    - Debug để hiểm thêm
 ***************************************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_ITEMS 5

int buffer[MAX_ITEMS];
int count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        while (count == MAX_ITEMS) {
            // buffer đầy, chờ consumer lấy bớt
            pthread_cond_wait(&cond, &mutex);
        }
        buffer[count++] = i;
        printf("Producer: thêm %d, count=%d\n", i, count);

        // báo cho một consumer biết có dữ liệu mới
        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);
        while (count == 0) {
            // buffer rỗng, chờ producer thêm dữ liệu
            pthread_cond_wait(&cond, &mutex);
        }
        int item = buffer[--count];
        printf("Consumer %ld: lấy %d, count=%d\n", (long)arg, item, count);

        // báo cho producer (hoặc các consumer khác) biết đã lấy bớt
        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons1, cons2;

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons1, NULL, consumer, (void*)1);
    pthread_create(&cons2, NULL, consumer, (void*)2);

    pthread_join(prod, NULL);
    pthread_join(cons1, NULL);
    pthread_join(cons2, NULL);

    return 0;
}
