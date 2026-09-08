#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void stop_thread() {
    printf("Stopping thread early...\n");
    pthread_exit("Stopped via helper function");
}

void* worker(void* arg) {
    printf("Worker thread started\n");
    sleep(2);
    stop_thread(); // gọi pthread_exit() từ hàm phụ
    return "Finished normally"; // sẽ không bao giờ chạy tới đây
}

int main() {
    pthread_t tid;

    // có thể dùng malloc để cấp phát động cho retval nếu muốn trả về dữ liệu từ thread
    void* retval; // retval nên được khai báo ở 1 vùng nhớ khác với stack của thread để tránh lỗi khi thread kết thúc

    pthread_create(&tid, NULL, worker, NULL);
    pthread_join(tid, &retval);

    printf("Thread returned: %s\n", (char*)retval);
    return 0;
}
