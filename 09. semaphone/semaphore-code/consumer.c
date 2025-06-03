#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define SEM_NAME "/mysem"

int main() {
    sem_t *sem = sem_open(SEM_NAME, 0);  // Mở semaphore đã tồn tại
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    printf("Consumer: Đang chờ tín hiệu từ producer...\n");
    sem_wait(sem);  // Chờ đến khi producer signal

    FILE *fp = fopen("data.txt", "r");
    if (!fp) {
        perror("fopen");
        exit(1);
    }

    char buffer[100];
    fgets(buffer, sizeof(buffer), fp);
    printf("Consumer: Đã đọc dữ liệu: %s", buffer);
    fclose(fp);

    sem_close(sem);
    sem_unlink(SEM_NAME);  // Xóa semaphore sau khi dùng

    return 0;
}
