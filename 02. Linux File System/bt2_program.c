#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Kiểm tra xem có đúng 4 tham số dòng lệnh không (bao gồm tên chương trình)
    if (argc != 5) {
        printf("Usage: ./example_program filename num-bytes [r/w] \"Hello\"\n");
        return 1;  // Nếu tham số không hợp lệ, in ra cách sử dụng và thoát
    }

    // Lấy các tham số dòng lệnh
    char *filename = argv[1];  // Tên file
    int num_bytes = atoi(argv[2]);  // Chuyển số byte từ chuỗi sang số nguyên
    char mode = argv[3][0];  // 'r' cho read, 'w' cho write
    char *data = argv[4];  // Dữ liệu muốn đọc hoặc ghi

    // Nếu chế độ là đọc ('r')
    if (mode == 'r') {
        // Mở file với quyền chỉ đọc (O_RDONLY)
        int fd = open(filename, O_RDONLY);
        if (fd < 0) {
            perror("open");  // In ra lỗi nếu không mở được file
            exit(1);
        }

        // Đọc num_bytes từ file vào buffer
        char buffer[num_bytes + 1];  // Để chứa dữ liệu và null-terminator
        int bytes_read = read(fd, buffer, num_bytes);  // Đọc dữ liệu vào buffer
        if (bytes_read < 0) {
            perror("read");  // In ra lỗi nếu không đọc được file
            close(fd);  // Đóng file
            exit(1);
        }

        // Đảm bảo kết thúc chuỗi đúng cách
        buffer[bytes_read] = '\0';
        printf("Data read from file: %s\n", buffer);  // In dữ liệu đã đọc từ file

        close(fd);  // Đóng file sau khi hoàn tất đọc
    } 
    // Nếu chế độ là ghi ('w')
    else if (mode == 'w') {
        // Mở file với quyền ghi (O_WRONLY) và tạo nếu chưa có (O_CREAT)
        int fd = open(filename, O_WRONLY | O_CREAT, 0644);
        if (fd < 0) {
            perror("open");  // In ra lỗi nếu không mở được file
            exit(1);
        }

        // Ghi dữ liệu vào file
        if (write(fd, data, num_bytes) == -1) {  // Ghi num_bytes dữ liệu vào file
            perror("write");  // In ra lỗi nếu không ghi được
            close(fd);  // Đóng file
            exit(1);
        }

        printf("Data written to file: %s\n", data);  // In ra dữ liệu đã ghi vào file

        close(fd);  // Đóng file sau khi hoàn tất ghi
    } 
    else {
        printf("Invalid mode. Use 'r' for read or 'w' for write.\n");
        return 1;  // Nếu mode không phải 'r' hoặc 'w', in lỗi và thoát
    }

    return 0;  // Chương trình thành công
}
