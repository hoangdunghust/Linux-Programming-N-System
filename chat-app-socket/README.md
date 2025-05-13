# 📡 Chat CLI App - TCP Socket Peer-to-Peer

Ứng dụng Chat dòng lệnh đơn giản sử dụng TCP Socket cho phép kết nối nhiều peer và gửi tin nhắn giữa các máy tính trong cùng mạng LAN.

## 🚀 Tính năng

- Hiển thị địa chỉ IP và cổng máy đang chạy
- Kết nối tới các máy khác trong mạng LAN qua IP và cổng
- Liệt kê các kết nối đang hoạt động
- Gán tên tùy chỉnh cho kết nối
- Gửi tin nhắn đến kết nối qua ID hoặc tên
- Ngắt kết nối bất kỳ peer nào
- Giao diện dòng lệnh đơn giản và dễ dùng

## 🧠 Kiến thức áp dụng

- TCP Socket trong Node.js (`net`)
- Xử lý dòng lệnh với `readline`
- Quản lý danh sách kết nối (connection pool)
- Tách module (helpers, connection...)

## Kiến thức cần có:
### readline là gì?
`readline` là một module trong Node.js cho phép bạn đọc và xử lý dòng lệnh từ người dùng.
### net là gì?
`net` là một module trong Node.js cho phép bạn tạo và quản lý các kết nối TCP
### connection pool là gì?
`connection pool` là một danh sách các kết nối được lưu trữ và có thể được sử dụng
### Tách module là gì?
Tách module là việc chia nhỏ mã nguồn thành các module nhỏ hơn, mỗi module có một chức năng riêng biệt.
###  process.exit(0) vs rl.close();
`process.exit(0)` sẽ thoát ứng dụng và kết thúc quá trình
`rl.close()` sẽ đóng kết nối readline và cho phép bạn tiếp tục sử dụng ứng dụng.
### TCP Socket là gì?
TCP Socket là một giao thức truyền thông tin được sử dụng để truyền dữ liệu giữa các máy tính


## ▶️ Chạy ứng dụng
Mỗi máy chạy 1 port khác nhau. Ví dụ:
`node app.js 9000`
Máy khác chạy:
`node app.js 9001`

## 💻 Câu lệnh CLI
Lệnh	Mô tả
help	Hiển thị danh sách lệnh
myip	Hiển thị IP của máy bạn
myport	Hiển thị cổng đang lắng nghe
connect <ip> <port>	Kết nối đến máy khác
list	Liệt kê các kết nối hiện tại
addname <id> <name>	Gán tên cho kết nối theo ID
send <id/tên> <tin nhắn>	Gửi tin nhắn đến peer theo ID hoặc tên
terminate <id>	Ngắt kết nối theo ID
exit	Thoát chương trình

## 📂 Cấu trúc thư mục

chat-app-socket/
│
├── app.js              # File chính chạy server & CLI
├── connection.js       # Quản lý kết nối TCP
├── helpers.js          # Hàm tiện ích (IP, kiểm tra IP hợp lệ, ...)
└── README.md           # Hướng dẫn sử dụng

## Ví dụ
> connect 192.168.56.1 9001
✅ Đã kết nối đến 192.168.56.1:9001
> addname 1 alice
✅ Đã gán tên 'alice' cho kết nối ID 1
> send alice hello
📤 Đã gửi đến alice (192.168.56.1:9001): hello
