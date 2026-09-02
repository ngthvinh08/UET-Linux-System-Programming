#include <pthread.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
    // ... sử dụng cond ...

    // Không bắt buộc phải gọi pthread_cond_destroy()
    // vì cond được khởi tạo tĩnh bằng macro PTHREAD_COND_INITIALIZER.
    // Nhưng nếu muốn tái khởi tạo lại, ta có thể destroy rồi init lại:
    pthread_cond_destroy(&cond);
    pthread_cond_init(&cond, NULL);

    return 0;
}
