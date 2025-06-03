#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int ret_val;
    int a = 0;

    printf("Giá trị ban đầu của a là: %d\n", a);

    ret_val = fork(); // Tạo tiến trình con

    if (ret_val == 0) {
        // 👉 Đây là tiến trình con
        a = 10;
        printf("🧒 [Con] Giá trị của a là: %d\n", a);
        printf("🧒 [Con] PID của tiến trình con là: %d\n", getpid());
        printf("🧒 [Con] PID của tiến trình cha là: %d\n", getppid());
    } else if (ret_val > 0) {
        // 👉 Đây là tiến trình cha
        printf("👨 [Cha] Giá trị của a là: %d\n", a);
        printf("👨 [Cha] PID của tiến trình cha là: %d\n", getpid());
        printf("👨 [Cha] PID của tiến trình con là: %d\n", ret_val);  // ✅ Sửa chỗ này
    } else {
        // fork() thất bại
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}
