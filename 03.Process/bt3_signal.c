#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

// Hàm xử lý tín hiệu trong tiến trình con
void signal_handler(int signum) {
    if (signum == SIGUSR1) {
        printf("Tiến trình con đã nhận tín hiệu SIGUSR1 từ cha.\n");
    }
}

int main() {
    pid_t pid = fork(); // Tạo tiến trình con

    if (pid < 0) {
        perror("fork thất bại");
        exit(1);
    }

    if (pid == 0) {
        // Đây là tiến trình con
        // Thiết lập xử lý tín hiệu SIGUSR1
        signal(SIGUSR1, signal_handler);

        printf("Tiến trình con đang đợi tín hiệu SIGUSR1...\n");

        // Dừng lại chờ tín hiệu (sử dụng pause)
        pause(); // Dừng tiến trình cho đến khi nhận tín hiệu
        printf("Tiến trình con kết thúc.\n");
    } else {
        // Đây là tiến trình cha
        // Đợi vài giây trước khi gửi tín hiệu
        sleep(3);

        printf("Tiến trình cha gửi tín hiệu SIGUSR1 đến con (PID = %d)...\n", pid);
        kill(pid, SIGUSR1); // Gửi tín hiệu SIGUSR1 đến con

        // Chờ tiến trình con kết thúc
        wait(NULL);
        printf("Tiến trình cha kết thúc.\n");
    }

    return 0;
}
