#include <stdio.h>
#include <unistd.h>     // fork(), getpid()
#include <sys/types.h>  // pid_t

int main() {
    pid_t pid = fork(); // tạo process con

    if (pid < 0) {
        // fork thất bại
        perror("fork thất bại");
        return 1;
    } else if (pid == 0) {
        // Đây là tiến trình con
        printf("Tiến trình con: PID = %d, Cha = %d\n", getpid(), getppid());
    } else {
        // Đây là tiến trình cha
        printf("Tiến trình cha: PID = %d, PID con = %d\n", getpid(), pid);
    }

    return 0;
}
