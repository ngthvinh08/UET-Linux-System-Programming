#include <pthread.h>
#include <stdlib.h>

int main() {
    pthread_cond_t *cond = malloc(sizeof(pthread_cond_t));
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_cond_init(cond, NULL);

    //  sử dụng cond ở đây 

    pthread_cond_destroy(cond);   // phải destroy trước khi free
    free(cond);

    return 0;
}
