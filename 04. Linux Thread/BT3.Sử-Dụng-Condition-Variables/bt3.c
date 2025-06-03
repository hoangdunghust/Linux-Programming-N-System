#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int data = 0;
int ready = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        int num = rand() % 10 + 1;
        pthread_mutex_lock(&mutex);
        data = num;
        ready = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        while (ready == 0) {
            pthread_cond_wait(&cond, &mutex);
        }
        printf("Consumer got data: %d\n", data);
        ready = 0;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    srand(time(NULL));

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
