Producer ghi dữ liệu vào một file tạm, Consumer chỉ đọc khi Producer hoàn thành ghi.
gcc producer.c -o producer -pthread
gcc consumer.c -o consumer -pthread
