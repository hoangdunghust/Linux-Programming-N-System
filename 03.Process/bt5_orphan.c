#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        sleep(10); // Cha đã chết khi con còn sống
        printf("Con (Orphan): Cha mới của tôi là PID = %d\n", getppid());
    } else {
        printf("Cha: Tôi sắp kết thúc. PID = %d\n", getpid());
        exit(0); // Kết thúc sớm
    }

    return 0;
}
