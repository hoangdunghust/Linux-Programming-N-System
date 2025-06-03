#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define SEM_NAME "/mysem"

int main() {
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 0);  // Khởi tạo với giá trị 0
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    FILE *fp = fopen("data.txt", "w");
    if (!fp) {
        perror("fopen");
        exit(1);
    }

    fprintf(fp, "Dữ liệu từ producer!\n");
    fclose(fp);
    printf("Producer: Đã ghi dữ liệu.\n");

    sem_post(sem);  // Tăng semaphore lên 1 – báo hiệu cho consumer
    printf("Producer: Đã signal consumer.\n");

    sem_close(sem);
    return 0;
}
