#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

 int main(){
    int fd = open("bt1_output.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd < 0) {
        perror("Lỗi mở file");
        return 1;
    }
lseek(fd, 0, SEEK_SET);
write(fd, "Hello\n", 6);
close(fd);

return 0;
}
