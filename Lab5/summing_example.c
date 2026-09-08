/*
------------------------------------------------------------
Example: Parallel Summation using Foster’s Method
------------------------------------------------------------
Step 1: Partitioning
    - Chia bài toán tổng từ 1 đến n thành các đoạn nhỏ (chunk)
      cho từng thread. Mỗi thread xử lý một phạm vi riêng.

Step 2: Communication
    - Mỗi thread tính tổng cục bộ (local_sum) và cộng vào biến
      tổng toàn cục (global_sum) được bảo vệ bằng mutex.

Step 3: Agglomeration
    - Mỗi thread xử lý nhiều phần tử trong phạm vi của nó thay vì
      chỉ một phần tử, để giảm overhead tạo thread.

Step 4: Mapping
    - Sử dụng static mapping: mỗi thread được gán một đoạn công việc
      có kích thước bằng nhau.

------------------------------------------------------------
Các API pthread đã sử dụng:
    - pthread_create()      : Tạo thread mới
    - pthread_join()        : Chờ thread kết thúc
    - pthread_mutex_init()  : Khởi tạo mutex
    - pthread_mutex_lock()  : Khóa mutex trước khi truy cập vùng chia sẻ
    - pthread_mutex_unlock(): Mở khóa mutex sau khi truy cập vùng chia sẻ
    - pthread_mutex_destroy(): Giải phóng mutex
------------------------------------------------------------
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 4
#define RANGE 10000000

long long total_sum = 0;
pthread_mutex_t lock;

void *sum_range(void *arg) {
    int *range = (int *)arg;
    int start = range[0];
    int end = range[1];
    long long local_sum = 0;

    for (int i = start; i <= end; i++) {
        local_sum += i;
    }

    pthread_mutex_lock(&lock);
    total_sum += local_sum;
    pthread_mutex_unlock(&lock);

    free(arg);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int chunk = RANGE / NUM_THREADS;

    pthread_mutex_init(&lock, NULL); // Khởi tạo mutex

    // Tạo các thread và phân chia phạm vi công việc
    for (int i = 0; i < NUM_THREADS; i++) {
        int *range = malloc(2 * sizeof(int)); // Xin 1 vùng nhớ cỡ 4 byte để lưu 2 giá trị start và end
        range[0] = i * chunk + 1;

        // Gán giá trị cho end = toán tử 3 ngôi
        // (condition) ? value_if_true : value_if_false;
        range[1] = (i == NUM_THREADS - 1) ? RANGE : (i + 1) * chunk;
        pthread_create(&threads[i], NULL, sum_range, range);
    }
    
    // Chờ tất cả các thread kết thúc
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Giải phóng mutex
    pthread_mutex_destroy(&lock);

    printf("Total sum from 1 to %d: %lld\n", RANGE, total_sum);
    return 0;
}
