#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 1000000
#define NUM_THREADS 4

int arr[ARRAY_SIZE];
long long total_sum = 0;
pthread_mutex_t mutex;

typedef struct {
    int start;
    int end;
} Range;

void* partial_sum(void* arg) {
    Range* range = (Range*)arg;
    long long sum = 0;
    for (int i = range->start; i < range->end; i++) {
        sum += arr[i];
    }
    pthread_mutex_lock(&mutex);
    total_sum += sum;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

    // Khởi tạo mảng
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = 1; // Hoặc random tùy ý
    }

    Range ranges[NUM_THREADS];
    int part_size = ARRAY_SIZE / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        ranges[i].start = i * part_size;
        ranges[i].end = (i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * part_size;
        pthread_create(&threads[i], NULL, partial_sum, &ranges[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Total sum: %lld\n", total_sum);

    pthread_mutex_destroy(&mutex);
    return 0;
}
