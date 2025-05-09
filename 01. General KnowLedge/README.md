# 🐧 Tổng hợp Kiến Thức Cơ Bản về Linux

Tài liệu này tổng hợp những kiến thức nền tảng và thiết yếu nhất về hệ điều hành **Linux**

---

## 📁 Mục lục

1. [Các lệnh cơ bản](#1-các-lệnh-cơ-bản)
2. [Hệ thống tập tin Linux](#2-hệ-thống-tập-tin-linux)
3. [Quản lý người dùng và phân quyền](#3-quản-lý-người-dùng-và-phân-quyền)
4. [Quản lý tiến trình](#4-quản-lý-tiến-trình)
5. [Bash scripting cơ bản](#5-bash-scripting-cơ-bản)
6. [Lịch trình tác vụ (Cron)](#6-lịch-trình-tác-vụ-cron)
7. [Mạng trong Linux](#7-mạng-trong-linux)
8. [Câu hỏi phỏng vấn thường gặp](#8-câu-hỏi-phỏng-vấn-thường-gặp)
9. [Bài tập](#9-bai-tap)

---

## 1. 🧰 Các lệnh cơ bản

| Lệnh    | Mô tả |
|------   |-------|
| `ls`    | Liệt kê thư mục/tệp |
| `cd`    | Di chuyển giữa các thư mục |
| `pwd`   | Hiển thị đường dẫn hiện tại |
| `cp`    | Sao chép tệp/thư mục |
| `mv`    | Di chuyển hoặc đổi tên |
| `rm`    | Xóa tệp/thư mục |
| `touch` | Tạo tệp mới |
| `mkdir` | Tạo thư mục |
| `cat`, `less`, `head`, `tail` | Xem nội dung tệp |
| `man`   | Xem hướng dẫn lệnh |
|`nano`   | Chỉnh sửa tệp văn bản |
|`vim`    | Chỉnh sửa tệp văn bản (có thể phức tạp hơn `nano`) |

---

## 2. 🗂️ Hệ thống tập tin Linux

Linux sử dụng hệ thống thư mục **dạng cây** bắt đầu từ `/`.

### Một số thư mục quan trọng:

- `/bin`, `/sbin`: chứa các lệnh hệ thống
- `/etc`: chứa tệp cấu hình
- `/home`: thư mục người dùng
- `/var`: log, cache và dữ liệu thay đổi
- `/tmp`: tệp tạm thời
- `/usr`: chứa phần mềm cài thêm

---

## 3. 🔐 Quản lý người dùng và phân quyền

### Quản lý user:
- Thêm người dùng: `sudo adduser tennguoidung`
- Xóa người dùng: `sudo deluser tennguoidung`
- Đổi mật khẩu người dùng `sudo passwd tennguoidung`
- Thêm người dùng vào nhóm sudo `sudo usermod -aG sudo tennguoidung`
Phân quyền:

chmod 755 file.txt       # rwxr-xr-x
chown user:group file    # đổi chủ sở hữu

### Ý nghĩa quyền (Permissions)
Mỗi tệp/thư mục có 3 nhóm quyền:

Nhóm	Mô tả
u	Chủ sở hữu (user)
g	Nhóm (group)
o	Khác (others)

### Quyền cơ bản:

Quyền	Ký hiệu	Giá trị
read	r	4 (100)
write	w	2 (010)
execute	x	1 (001)

Ví dụ: quyền rwxr-xr-- tương đương:

User: rwx = 7 = 4+2+1 (111)

Group: r-x = 5 = 4+1 (101)

Others: r-- = 4 (100)
⟶ chmod: chmod 754 filename

### Câu lệnh phân quyền
Mục đích	Lệnh
Thay đổi quyền (số)	|`chmod 755 file`|
Thay đổi quyền (ký hiệu)	|`chmod u+x file`|
Thay đổi chủ sở hữu	| `chown user file`|
Thay đổi nhóm	|`chgrp group file`
Cả chủ và nhóm	|`chown user:group file`|

### Lưu ý đặc biệt
|`chmod 777`  | Mọi người đều có toàn quyền (❗rất nguy hiểm)

|`chmod 400`  | Chỉ chủ sở hữu có quyền đọc (thường dùng cho SSH key)

chmod +x script.sh: Cấp quyền thực thi cho script
---

## 4. ⚙️ Quản lý tiến trình
Tác vụ	Lệnh
Xem tiến trình	`ps aux, top, htop`
Dừng tiến trình	`kill PID, killall tên`
Chạy nền	`command &`
Chạy không bị ngắt	`nohup command &`

## 5. 💻 Bash scripting cơ bản
Ví dụ đơn giản:
\`
#!/bin/bash

echo "Xin chào $USER"

for i in {1..5}
do
  echo "Dòng số $i"
done
\`
Câu lệnh cơ bản:
Gán biến: a=10

Đọc input: read var

Câu lệnh điều kiện: if, else, elif

Vòng lặp: for, while, until

## 6. 🕒 Lịch trình tác vụ (Cron)
Mở bảng crontab:

crontab -e
Cấu trúc:

* * * * * lệnh
│ │ │ │ └── Thứ (0–7)
│ │ │ └──── Tháng (1–12)
│ │ └────── Ngày (1–31)
│ └──────── Giờ (0–23)
└────────── Phút (0–59)
Ví dụ: chạy mỗi ngày lúc 2h sáng

0 2 * * * /home/user/backup.sh
## 7. 🌐 Mạng trong Linux
Tác vụ	Lệnh
Xem IP	ip a, ifconfig
Kiểm tra kết nối	ping, curl, netstat, ss

Quản lý tường lửa với UFW:

sudo ufw enable
sudo ufw allow 22
sudo ufw status
## 8. ❓ Câu hỏi phỏng vấn thường gặp
Fork và exec là gì?

Phân biệt Hard link và Symbolic link

systemd là gì? So sánh với SysVinit

Cách giám sát log real-time?

Vì sao chmod 400 cho private key?
## 9. Bài tập
| Điểm khác      | Static (`.a`)  | Shared (`.so`)                            |
| -------------- | -------------- | ----------------------------------------- |
| Flag biên dịch | `-c`           | `-fPIC -c`                                |
| Tạo thư viện   | `ar rcs lib.a` | `gcc -shared -o lib.so`                   |
| Khi chạy       | Không cần `.a` | Cần `.so` có sẵn hoặc dùng `-Wl,-rpath=.` |
