/* 
- It is not necessary to call pthread_mutex_destroy() on a mutex that was statically initialized using PTHREAD_MUTEX_INITIALIZER
- It is safe to destroy a mutex only when it is unlocked, and no thread will subsequently try to lock it
- If the mutex resides in a region of dynamically allocated memory, then it should be destroyed before freeing that memory region
- An automatically allocated mutex should be destroyed before its host function returns
*/ 


/*********************************** DYNAMIC ALLOCATED MUTEX *******************************************/
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int data;
    pthread_mutex_t lock;
} Shared;

int main(void) {
    Shared *sh = malloc(sizeof(Shared));
    pthread_mutex_init(&sh->lock, NULL);

    // sử dụng sh->lock để bảo vệ sh->data
    pthread_mutex_lock(&sh->lock);
    sh->data = 42;
    pthread_mutex_unlock(&sh->lock);

    // hủy mutex trước khi free vùng nhớ
    pthread_mutex_destroy(&sh->lock);
    free(sh);

    return 0;
}
