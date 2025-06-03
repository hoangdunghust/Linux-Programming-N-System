#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;
int counter = 2;

void *count1(void *arg)
{

    pthread_mutex_lock(&lock); // Bắt đầu vùng bảo vệ
    printf("Thread 1: %d\n", ++counter);
    sleep(5);
    pthread_mutex_unlock(&lock); // Kết thúc vùng bảo vệ
    pthread_exit(NULL);
    return NULL;
}

void *count2(void *arg)
{
    pthread_mutex_lock(&lock); // Bắt đầu vùng bảo vệ
    printf("Thread 2: %d\n", ++counter);
    sleep(5);
    pthread_mutex_unlock(&lock); // Kết thúc vùng bảo vệ
    pthread_exit(NULL);
    return NULL;
}
int main()
{
    int ret;
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);

    if (ret = pthread_create(&t1, NULL, count1, NULL))
    {
        printf("Error creating thread 1: %d\n", ret);
        return -1;
    }

    if (ret = pthread_create(&t2, NULL, count2, NULL))
    {
        printf("Error creating thread 2: %d\n", ret);
        return -1;
    }
    pthread_mutex_init(&lock, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}
