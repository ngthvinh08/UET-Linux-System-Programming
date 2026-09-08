/*
------------------------------------------------------------
Example: Parallel String Search using pthread
------------------------------------------------------------
Step 1: Partitioning
    - Chia mảng chuỗi thành các chunk cho từng thread.

Step 2: Communication
    - Mỗi thread tìm target trong chunk của nó.
    - Nếu tìm thấy, đặt shared flag và lưu index.

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
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUM_THREADS 4
#define ARRAY_SIZE 1000

char *data[ARRAY_SIZE];       // mảng chuỗi
char target[] = "hello";      // chuỗi cần tìm
int found_index = -1;         // vị trí tìm thấy
int found_flag = 0;           // cờ chung
pthread_mutex_t lock;

void *search_chunk(void *arg) {
    int *range = (int *)arg;
    int start = range[0];
    int end = range[1];

    for (int i = start; i <= end && !found_flag; i++) {
        if (strcmp(data[i], target) == 0) {
            pthread_mutex_lock(&lock);
            if (!found_flag) { // kiểm tra lại để tránh race condition
                found_flag = 1;
                found_index = i;
            }
            pthread_mutex_unlock(&lock);
            break; // dừng thread này
        }
    }

    free(range);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int chunk = ARRAY_SIZE / NUM_THREADS;

    // Khởi tạo dữ liệu giả lập
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data[i] = (i == 567) ? "hello" : "world"; // target ở vị trí 567
    }

    pthread_mutex_init(&lock, NULL);

    // Tạo thread
    for (int i = 0; i < NUM_THREADS; i++) {
        int *range = malloc(2 * sizeof(int));
        range[0] = i * chunk;
        range[1] = (i == NUM_THREADS - 1) ? ARRAY_SIZE - 1 : (i + 1) * chunk - 1;

        pthread_create(&threads[i], NULL, search_chunk, range);
    }

    // Chờ thread kết thúc
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    if (found_flag) {
        printf("Target string '%s' found at index %d\n", target, found_index);
    } else {
        printf("Target string '%s' not found\n", target);
    }

    return 0;
}
