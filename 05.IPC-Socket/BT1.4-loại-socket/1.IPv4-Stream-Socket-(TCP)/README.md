✅ 1. Server chỉ chấp nhận và xử lý 1 client
Bạn chưa dùng while() hay fork() hoặc pthread để xử lý nhiều client. Nó chỉ:

Chấp nhận 1 kết nối (accept)

Nhận dữ liệu

Trả lời lại

Đóng socket
=> Kết thúc chương trình.

✅ 2. Client gửi một lần rồi thoát
Gửi "Hello from client!" qua write()

Đọc phản hồi từ server qua read()

In ra rồi close()
=> Thoát chương trình.