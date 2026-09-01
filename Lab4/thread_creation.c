#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Hàm mà thread sẽ thực thi
void* thread_function(void* arg) {
    int thread_num = *((int*)arg);
    printf("Hello from thread %d!\n", thread_num);
    pthread_exit(NULL); // kết thúc thread
}

int main() {
    pthread_t threads_id[3];   // mảng chứa ID của các thread
    int thread_args[3];     // mảng chứa tham số truyền vào thread

    for (int i = 0; i < 3; i++) {
        thread_args[i] = i;
        // tạo thread mới
        int rc = pthread_create(&threads_id[i],    // ID
                                NULL,           // attributes
                                thread_function, // function to execute
                                (void*)&thread_args[i]);    // arguments to function
        
        // pthread_create trả về 0 nếu thành công, ngược lại trả về mã lỗi
        if (rc) {
            fprintf(stderr, "Error: pthread_create() failed with code %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    // chờ các thread kết thúc
    for (int i = 0; i < 3; i++) {
        // hàm dùng để chờ một thread kết thúc
        pthread_join(threads_id[i], NULL);
    }

    printf("All threads finished.\n");
    return 0;
}
