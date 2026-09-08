/* 
- It is not necessary to call pthread_mutex_destroy() on a mutex that was statically initialized using PTHREAD_MUTEX_INITIALIZER
- It is safe to destroy a mutex only when it is unlocked, and no thread will subsequently try to lock it
- If the mutex resides in a region of dynamically allocated memory, then it should be destroyed before freeing that memory region
- An automatically allocated mutex should be destroyed before its host function returns
*/ 


/*********************************** DYNAMIC ALLOCATED MUTEX IN A FUNCTION ***********************************/
#include <pthread.h>
#include <stdio.h>

void doWork(void) {
    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);

    pthread_mutex_lock(&lock);
    printf("Critical section\n");
    pthread_mutex_unlock(&lock);

    // hủy mutex trước khi hàm kết thúc
    pthread_mutex_destroy(&lock);
}

int main(void) {
    doWork();
    return 0;
}
