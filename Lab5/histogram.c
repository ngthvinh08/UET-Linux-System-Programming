/*
------------------------------------------------------------
Example: Parallel Histogram Calculator using pthread
------------------------------------------------------------
Step 1: Partitioning
    - Chia mảng dữ liệu thành các chunk cho từng thread.

Step 2: Communication
    - Mỗi thread tính histogram cục bộ (local_histogram).
    - Sau đó cộng kết quả vào histogram toàn cục (global_histogram)
      được bảo vệ bằng mutex.

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
#include <pthread.h>

#define NUM_THREADS 4
#define RANGE 1000000   // số phần tử trong mảng
#define MAX_VALUE 256   // giá trị từ 0-255

int *data;
int global_histogram[MAX_VALUE] = {0};
pthread_mutex_t lock;

void *compute_histogram(void *arg) {
    int *range = (int *)arg;
    int start = range[0];
    int end = range[1];
    int local_histogram[MAX_VALUE] = {0};

    // Đếm tần suất trong chunk
    for (int i = start; i <= end; i++) {
        local_histogram[data[i]]++;
    }

    // Cộng kết quả vào histogram toàn cục
    pthread_mutex_lock(&lock);
    for (int v = 0; v < MAX_VALUE; v++) {
        global_histogram[v] += local_histogram[v];
    }
    pthread_mutex_unlock(&lock);

    free(range);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int chunk = RANGE / NUM_THREADS;

    // Khởi tạo dữ liệu giả lập (giá trị từ 0-255)
    data = malloc(RANGE * sizeof(int));
    for (int i = 0; i < RANGE; i++) {
        data[i] = rand() % MAX_VALUE;
    }

    pthread_mutex_init(&lock, NULL);

    // Tạo thread
    for (int i = 0; i < NUM_THREADS; i++) {
        int *range = malloc(2 * sizeof(int));
        range[0] = i * chunk;
        range[1] = (i == NUM_THREADS - 1) ? RANGE - 1 : (i + 1) * chunk - 1;

        pthread_create(&threads[i], NULL, compute_histogram, range);
    }

    // Chờ thread kết thúc
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    // In kết quả histogram
    for (int v = 0; v < MAX_VALUE; v++) {
        printf("Value %d: %d\n", v, global_histogram[v]);
    }

    free(data);
    return 0;
}
