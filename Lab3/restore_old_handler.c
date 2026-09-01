#include <stdio.h>
#include <signal.h>

void my_handler(int sig) {
    printf("Caught signal %d\n", sig);
}

int main() {
    void (*old_handler)(int); // Khai báo con trỏ hàm tới 1 hàm có dạng f(int) và trả về void

    // Đăng ký handler mới cho SIGINT
    old_handler = signal(SIGINT, my_handler);

    // Khi signal() thành công sẽ trả về handler cũ, nếu không thành công sẽ trả về SIG_ERR
    // Kiểm tra handler cũ
    // SIG_DFL (Default): nghĩa là trước đó tín hiệu này được xử lý theo cách mặc định của hệ thống. Ví dụ: SIGINT mặc định sẽ kết thúc chương trình.
    // SIG_IGN (Ignore): nghĩa là trước đó tín hiệu này bị bỏ qua, không làm gì cả.
    // Một hàm handler cụ thể: nghĩa là trước đó đã có một hàm do người lập trình định nghĩa để xử lý tín hiệu này.
    if (old_handler == SIG_DFL) {
        printf("Trước đó SIGINT đang dùng handler mặc định.\n");
    } else if (old_handler == SIG_IGN) {
        printf("Trước đó SIGINT đang bị bỏ qua.\n");
    } else {
        printf("Trước đó SIGINT có handler riêng.\n");
    }

    while (1); // Chạy vô hạn để test Ctrl+C
}
