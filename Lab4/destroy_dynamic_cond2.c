#include <pthread.h>

void my_function() {
    pthread_cond_t cond;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_cond_init(&cond, NULL);

    //  sử dụng cond trong phạm vi hàm 

    pthread_cond_destroy(&cond);  // destroy trước khi hàm kết thúc
}
