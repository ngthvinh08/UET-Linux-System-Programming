/*
------------------------------------------------------------
Example: Parallel Matrix Multiplication using pthread
------------------------------------------------------------
Step 1: Partitioning
    - Chia công việc theo hàng: mỗi thread tính toàn bộ một hàng của ma trận C.

Step 2: Communication
    - Các thread độc lập tính toán, không cần chia sẻ dữ liệu trong quá trình nhân.
    - Kết quả được ghi trực tiếp vào ma trận C toàn cục.

Step 3: Agglomeration
    - Mỗi thread xử lý nhiều phần tử (toàn bộ một hàng) thay vì chỉ một phần tử.

Step 4: Mapping
    - Static mapping: mỗi thread được gán một hàng cố định.

------------------------------------------------------------
Các API pthread đã sử dụng:
    - pthread_create()      : Tạo thread
    - pthread_join()        : Chờ thread kết thúc
------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 4
#define NUM_THREADS N

int A[N][N], B[N][N], C[N][N];

void *multiply_row(void *arg) {
    int row = *(int *)arg;
    free(arg);

    for (int j = 0; j < N; j++) {
        C[row][j] = 0;
        for (int k = 0; k < N; k++) {
            C[row][j] += A[row][k] * B[k][j];
        }
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Khởi tạo dữ liệu mẫu
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = i + j;   // ví dụ: A[i][j] = i+j
            B[i][j] = i - j;   // ví dụ: B[i][j] = i-j
        }
    }

    // Tạo thread cho mỗi hàng
    for (int i = 0; i < NUM_THREADS; i++) {
        int *row = malloc(sizeof(int));
        *row = i;
        pthread_create(&threads[i], NULL, multiply_row, row);
    }

    // Chờ tất cả thread kết thúc
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // In kết quả
    printf("Matrix C = A * B:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
