#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Chương trình hiện tại là C\n");

    // Thay thế tiến trình hiện tại bằng lệnh `ls -l`
    execl("/bin/ls", "ls", "-l", NULL);

    // Dòng này sẽ không được in ra nếu execl thành công
    printf("Dòng này sẽ không được in ra.\n");

    return 0;
}
