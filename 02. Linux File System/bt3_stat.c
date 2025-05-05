#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

int main() {
    // Tạo file và ghi dữ liệu vào file
    const char *filename = "bt3_output.txt";
    const char *data = "This is a test file for BT3.\n";

    // Mở file (O_CREAT tạo mới nếu chưa có, O_WRONLY chỉ ghi, O_TRUNC ghi đè lên nội dung cũ)
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Ghi dữ liệu vào file
    if (write(fd, data, strlen(data)) == -1) {
        perror("write");
        close(fd);
        exit(1);
    }

    // Đóng file
    close(fd);

    // Lấy thông tin file
    struct stat file_stat;
    if (stat(filename, &file_stat) == -1) {
        perror("stat");
        exit(1);
    }

    // In thông tin file
    printf("File name: %s\n", filename);

    // Kiểm tra loại file
    if (S_ISREG(file_stat.st_mode)) {
        printf("File type: Regular File\n");
    } else {
        printf("File type: Other\n");
    }

    // Thời gian chỉnh sửa lần cuối
    printf("Last modified: %s", ctime(&file_stat.st_mtime));

    // Kích thước file
    printf("File size: %ld bytes\n", file_stat.st_size);

    return 0;
}
