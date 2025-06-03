#include <stdio.h>
#include <pthread.h>

void* thread_func(void* arg) {
    pthread_t tid = pthread_self();
    printf("Thread ID: %lu says hello\n", (unsigned long)tid);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread_func, NULL);
    pthread_create(&t2, NULL, thread_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main thread: Both threads finished\n");
    return 0;
}
