# Tổng Quan Hệ Thống Tập Tin Trong Linux

## 1. Giới thiệu về Hệ thống Tập tin Linux (Linux File System)

Hệ thống tập tin (File System) trong Linux là một cách tổ chức và quản lý dữ liệu trên ổ đĩa, từ các tệp tin, thư mục cho đến các thông tin hệ thống quan trọng. Linux sử dụng một hệ thống tập tin dạng cây, trong đó các thư mục con được tổ chức dưới thư mục gốc `/`. Tất cả mọi thứ trong Linux đều được xem là một tệp tin, bao gồm cả thiết bị phần cứng, thư mục và các phần mềm.
### Các loại file
- **Regular file** (tệp tin thường): Đây là loại tệp tin thông thường
- **Directory** (thư mục): Là một loại tệp tin đặc biệt
- **Block device** (thiết bị khối): Là một loại tệp tin đặc biệt
- **Character device** (thiết bị ký tự): Là một loại tệp tin đặc
- **Link file** (tệp liên kết): Là một loại tệp tin đặc biệt
- **Socket** (cổng): Là một loại tệp tin đặc biệt
- **Pipe file** (tệp ống): Là một loại tệp tin đặc biệt
### Đặc điểm chính:
- **Tệp tin là đối tượng duy nhất trong Linux**: Dữ liệu, thư mục và thiết bị đều được biểu diễn dưới dạng tệp tin.
- **Cấu trúc cây**: Hệ thống tập tin Linux bắt đầu từ thư mục gốc `/` và phân nhánh thành các thư mục con.
- **Định dạng hệ thống tập tin**: Hỗ trợ nhiều định dạng như `ext4`, `xfs`, `btrfs`, `vfat`, `ntfs`.

---

## 2. Các thao tác trên tệp (File Operations)

### Tạo tệp:

touch file.txt
### Đọc tệp:

cat file.txt
### Ghi vào tệp:

echo "Hello, Linux" > file.txt
### Chỉnh sửa tệp:
Sử dụng trình soạn thảo văn bản như: nano, vim, emacs.

### Xóa tệp:

rm file.txt
### Di chuyển hoặc đổi tên tệp:

mv old_name.txt new_name.txt
### Sao chép tệp:

cp file.txt /new/location/file.txt
### Kiểm tra thông tin tệp:

stat file.txt
### Các lời gọi hệ thống(system call)
user space thực hiện thông qua kernel space để thao tác với hardware 
#### open()
#### read()
#### write()
#### close()
#### lseek()
## 3. Quản lý Tệp trong Hệ thống Tập tin (File Management)
### Tạo thư mục:

mkdir new_folder
### Xem nội dung thư mục:

ls
### Thay đổi quyền truy cập:

chmod 755 file.txt
### Thay đổi chủ sở hữu:

chown user:user file.txt
### Kiểm tra dung lượng:

du -sh file.txt
### Quản lý các loại tệp:
  Linux hỗ trợ nhiều loại tệp như tệp thông thường, thư mục, liên kết mềm (symbolic links), liên kết cứng (hard links), tệp thiết bị, v.v.
## 4. Khóa têp( File Loking)
Khóa tệp là một cơ chế dùng để ngăn chặn nhiều tiến trình truy cập vào tệp đồng thời, tránh xung đột khi đọc/ghi tệp. Hệ thống tập tin Linux hỗ trợ hai loại khóa tệp chính:

Khóa tệp mềm (Soft Locking): Được thực hiện qua các hệ thống quản lý tệp, khóa này có thể bị bỏ qua hoặc thay đổi khi có yêu cầu.

Khóa tệp cứng (Hard Locking): Được hệ thống đảm bảo, chỉ một tiến trình có thể giữ khóa tệp tại một thời điểm.
### các phương pháp khóa tệp phổ biến:
 - fcntl() : Được dùng cho việc kiểm soát khóa tệp ở mức độ hệ thống. Phạm vi sử dụng trong một vùng trong file
 - flock() :  Được sử dụng để khóa tệp trong các ứng dụng sử dụng hệ thống tệp hỗ trợ flock. Phạm vi hoạt động toàn bộ file
 - lockf() :  Được dùng để khóa tệp trong các ứng dụng sử dụng hệ thống
 flock được sử dụng nhiều hơn 
 ### synchronization(đồng bộ)
 - thực hiện cùng một lúc
 ### asynchronization(bất dồng bộ)
 - thực hiện theo thứ tự
 ### thuật toán 
 - round robin: xoay vòng
 - time sharing: chia sẻ thời gian
 - shortest job first: ít thời gian nhất thì dc chạy trước
 ## bài tập
 ### BT1.
 Viết một chương trình mở một file bất kì và sử dụng cờ O_APPEND, sau đó thực hiện seek về đầu file rồi ghi một vài dữ  liệu vào file đó. Dữ liệu sẽ xuất hiện ở vị trí nào của file và tại sao lại như vậy?
 ### BT2.
 Viết một chương trình có só lượng command-line arguments là 3, có dạng như sau: $ ./example_program filename num-bytes [r/w] "Hello"
 Trong đó:
	1. example_grogram: Tên file thực thi
	2. filename: Tên file
	3. num-bytes: Số byte muốn read/write
	4. [r/w]: r -> Thực hiện đọc từ  filename và in ra màn hình
		    w -> Thực hiện ghi vào filename
	5. "Hello": Nội dung bất kì muốn read/write vào filename
 ### BT3.
Tạo file bất kì và ghi một đoạn dữ liệu vào file đó. Thực hiện ghi ra màn hình các thông tin: Loại file, tên file, thời gian chỉnh sửa file lần cuối, kích thước. - Sử dụng struct stat
