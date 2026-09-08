/*
------------------------------------------------------------
Example: Parallel Quicksort using pthread
------------------------------------------------------------
Step 1: Partitioning
    - Chọn pivot, chia mảng thành hai phần: nhỏ hơn pivot và lớn hơn pivot.

Step 2: Communication
    - Mỗi thread sắp xếp một phần mảng. Kết quả được ghi trực tiếp vào mảng toàn cục.

Step 3: Agglomeration
    - Mỗi thread xử lý nhiều phần tử (một phân vùng) thay vì chỉ một phần tử.

Step 4: Mapping
    - Tạo thread mới cho mỗi phân vùng. Có thể giới hạn độ sâu để tránh tạo quá nhiều thread.

------------------------------------------------------------
Các API pthread đã sử dụng:
    - pthread_create()      : Tạo thread
    - pthread_join()        : Chờ thread kết thúc
------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 8   // giới hạn số thread để tránh quá tải

typedef struct {
    int *arr;
    int left;
    int right;
    int depth;
} Args;

int thread_count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[right]);
    return i + 1;
}

void *quicksort(void *arg) {
    Args *args = (Args *)arg;
    int left = args->left;
    int right = args->right;
    int *arr = args->arr;
    int depth = args->depth;
    free(arg);

    if (left < right) {
        int pi = partition(arr, left, right);

        // tạo thread cho phân vùng trái
        pthread_t tid_left, tid_right;
        int created_left = 0, created_right = 0;

        if (depth < MAX_THREADS) {
            Args *left_args = malloc(sizeof(Args));
            left_args->arr = arr;
            left_args->left = left;
            left_args->right = pi - 1;
            left_args->depth = depth + 1;
            pthread_create(&tid_left, NULL, quicksort, left_args);
            created_left = 1;
        } else {
            Args left_args = {arr, left, pi - 1, depth + 1};
            quicksort(&left_args);
        }

        if (depth < MAX_THREADS) {
            Args *right_args = malloc(sizeof(Args));
            right_args->arr = arr;
            right_args->left = pi + 1;
            right_args->right = right;
            right_args->depth = depth + 1;
            pthread_create(&tid_right, NULL, quicksort, right_args);
            created_right = 1;
        } else {
            Args right_args = {arr, pi + 1, right, depth + 1};
            quicksort(&right_args);
        }

        if (created_left) pthread_join(tid_left, NULL);
        if (created_right) pthread_join(tid_right, NULL);
    }
    return NULL;
}

int main() {
    int n = 20;
    int arr[20];

    // Khởi tạo dữ liệu ngẫu nhiên
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    printf("Original array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    Args *args = malloc(sizeof(Args));
    args->arr = arr;
    args->left = 0;
    args->right = n - 1;
    args->depth = 0;

    quicksort(args);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
