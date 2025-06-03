#include <stdio.h>
#include <pthread.h>

int counter = 0;

void* increment(void* arg) {
    for (int i = 0; i < 100000; ++i)
        counter++;
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Counter = %d\n", counter);
    return 0;
}
// 🔻 Kỳ vọng: counter = 200000
// ❌ Thực tế: Có thể là 175000, 189000... tuỳ lần chạy.
// Nếu 2 thread cùng thực hiện các bước trên cùng lúc → chúng sẽ ghi đè lên nhau → mất dữ liệu.


// cách khắc phục:

// pthread_mutex_t lock;

// void* increment(void* arg) {
//     for (int i = 0; i < 100000; ++i) {
//         pthread_mutex_lock(&lock);
//         counter++;
//         pthread_mutex_unlock(&lock);
//     }
//     return NULL;
// }
