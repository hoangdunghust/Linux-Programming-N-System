lseek(fd, 5, SEEK_SET)
SEEK_SET DI CHUYỂN VỀ ĐẦU FILE
SEEK_END DI CHUYỂN VỀ CUỐI FILE
lseek(fd, -6, SEEK_END) ĐỂ TRỎ VỀ CUỐI FILE VÀ DI CHUYỂN VỀ TRƯỚC 6 BYTE
mở một file với cờ O_APPEND, con trỏ ghi (write pointer) sẽ tự động được di chuyển đến cuối file mỗi khi bạn ghi dữ liệu vào file. Điều này có nghĩa là dữ liệu mới luôn được ghi vào cuối file, bất kể bạn có sử dụng lệnh lseek() để di chuyển con trỏ file hay không.
