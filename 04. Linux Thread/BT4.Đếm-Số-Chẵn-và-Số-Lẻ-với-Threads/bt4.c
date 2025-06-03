#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int arr[100];
int even_count = 0;
int odd_count = 0;

void* count_even(void* arg) {
    for (int i = 0; i < 100; i++) {
        if (arr[i] % 2 == 0) even_count++;
    }
    return NULL;
}

void* count_odd(void* arg) {
    for (int i = 0; i < 100; i++) {
        if (arr[i] % 2 != 0) odd_count++;
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    for (int i = 0; i < 100; i++) {
        arr[i] = i + 1;
    }

    pthread_create(&t1, NULL, count_even, NULL);
    pthread_create(&t2, NULL, count_odd, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Even count: %d\n", even_count);
    printf("Odd count: %d\n", odd_count);

    return 0;
}
