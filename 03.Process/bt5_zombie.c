#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Con (Zombie): PID = %d\n", getpid());
        exit(0); // Con kết thúc
    } else {
        printf("Cha: PID = %d, Con PID = %d\n", getpid(), pid);
        sleep(20); // Không gọi wait() -> con thành zombie
    }

    return 0;
}


