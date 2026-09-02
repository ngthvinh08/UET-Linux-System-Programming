#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Sai: trả về địa chỉ biến trên stack
void* bad_worker(void* arg) {
    int result = 42;
    return &result; // vùng nhớ này sẽ mất khi thread kết thúc
}

// Đúng: dùng malloc để cấp phát động
void* good_worker(void* arg) {
    int* result = malloc(sizeof(int));
    *result = 99;
    return result; // vùng nhớ này vẫn tồn tại sau khi thread chết
}

int main() {
    pthread_t tid1, tid2;
    void* retval1;
    void* retval2;

    pthread_create(&tid1, NULL, bad_worker, NULL);
    pthread_create(&tid2, NULL, good_worker, NULL);

    pthread_join(tid1, &retval1);
    pthread_join(tid2, &retval2);

    // In kết quả
    printf("Bad worker returned: %d (không an toàn)\n", *(int*)retval1);
    printf("Good worker returned: %d (an toàn)\n", *(int*)retval2);

    free(retval2); // giải phóng bộ nhớ động
    return 0;
}
