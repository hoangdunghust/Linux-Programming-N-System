#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("Lỗi fork");
        exit(1);
    }

    if (pid == 0) {
        // Tiến trình con
        printf("Con: PID = %d\n", getpid());
        exit(10);  // Kết thúc với mã 10
    } else {
        // Tiến trình cha
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Cha: Con kết thúc với mã = %d\n", WEXITSTATUS(status));
        } else {
            printf("Cha: Con kết thúc bất thường.\n");
        }
    }

    return 0;
}
