/*
 * Ví dụ: Tạo thread detached ngay khi khởi tạo
 *
 * System calls / API:
 * - pthread_attr_init(): khởi tạo cấu trúc thuộc tính với giá trị mặc định.
 * - pthread_attr_setdetachstate(): thay đổi trạng thái thành detached.
 * - pthread_create(): tạo thread mới với thuộc tính đã chỉnh.
 * - pthread_attr_destroy(): giải phóng cấu trúc thuộc tính sau khi dùng.
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* threadFunc(void* arg) {
    printf("Hello từ detached thread!\n");
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_attr_t attr;

    // Khởi tạo thuộc tính với giá trị mặc định
    pthread_attr_init(&attr);

    // Thiết lập trạng thái detached
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // Tạo thread với thuộc tính đã chỉnh
    pthread_create(&thread, &attr, threadFunc, NULL);

    // Không cần join, thread sẽ tự giải phóng khi kết thúc
    pthread_attr_destroy(&attr); // Giải phóng cấu trúc thuộc tính sau khi dùng

    printf("Hello từ main thread!\n");

    // Ngủ một chút để detached thread có thời gian chạy
    sleep(1);

    return 0;
}
