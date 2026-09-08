/*
------------------------------------------------------------
Example: Parallel Odd Number Counting using pthread
------------------------------------------------------------
Step 1: Partitioning
    - Chia phạm vi [1..RANGE] thành các đoạn (chunk) cho từng thread.

Step 2: Communication
    - Mỗi thread tính số lượng số lẻ trong đoạn của nó.
    - Kết quả cục bộ cộng vào biến toàn cục (global_count) được bảo vệ bằng mutex.

Step 3: Agglomeration
    - Mỗi thread xử lý nhiều phần tử trong chunk thay vì chỉ một phần tử.

Step 4: Mapping
    - Static mapping: mỗi thread được gán một chunk bằng nhau.

------------------------------------------------------------
Các API pthread đã sử dụng:
    - pthread_create()      : Tạo thread
    - pthread_join()        : Chờ thread kết thúc
    - pthread_mutex_init()  : Khởi tạo mutex
    - pthread_mutex_lock()  : Khóa mutex
    - pthread_mutex_unlock(): Mở khóa mutex
    - pthread_mutex_destroy(): Giải phóng mutex
------------------------------------------------------------
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 4
#define RANGE 10000000

long long global_count = 0;
pthread_mutex_t lock;

void *count_odds(void *arg) {
    int *range = (int *)arg;
    int start = range[0];
    int end = range[1];
    long long local_count = 0;

    for (int i = start; i <= end; i++) {
        if (i % 2 != 0) { // kiểm tra số lẻ
            local_count++;
        }
    }

    pthread_mutex_lock(&lock);
    global_count += local_count;
    pthread_mutex_unlock(&lock);

    free(range);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int chunk = RANGE / NUM_THREADS;

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        int *range = malloc(2 * sizeof(int));
        range[0] = i * chunk + 1;
        range[1] = (i == NUM_THREADS - 1) ? RANGE : (i + 1) * chunk;

        pthread_create(&threads[i], NULL, count_odds, range);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    printf("Total odd numbers from 1 to %d: %lld\n", RANGE, global_count);
    return 0;
}
