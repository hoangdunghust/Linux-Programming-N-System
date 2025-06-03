#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int data = 0;
pthread_rwlock_t rwlock;

void* reader(void* arg) {
    pthread_rwlock_rdlock(&rwlock);
    printf("Reader thread read data = %d\n", data);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

void* writer(void* arg) {
    pthread_rwlock_wrlock(&rwlock);
    data++;
    printf("Writer thread incremented data to %d\n", data);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

int main() {
    pthread_t readers[5], writers[2];
    pthread_rwlock_init(&rwlock, NULL);

    for (int i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    printf("Final data value: %d\n", data);

    pthread_rwlock_destroy(&rwlock);
    return 0;
}
