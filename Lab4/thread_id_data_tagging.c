#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Dùng thread ID để định danh dữ liệu gắn với thread
// Cấu trúc dữ liệu có gắn thread ID
typedef struct {
    pthread_t owner;
    int value;
} Resource;

void* worker(void* arg) {
    Resource* res = malloc(sizeof(Resource));
    res->owner = pthread_self(); // gắn thread ID vào resource
    res->value = rand() % 100;

    // Kiểm tra thread hiện tại có phải chủ sở hữu không
    if (pthread_equal(res->owner, pthread_self())) {
        printf("Thread %lu owns resource with value %d\n",
               res->owner, res->value);
    }

    free(res);
    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, worker, NULL);
    pthread_create(&tid2, NULL, worker, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}
