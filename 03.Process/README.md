# Linux process
## 1. Introduction
### Process(Tiến trình)
- Process là một chương trình đang được thực thi (đang chạy)
- Mỗi process có thể được phân biệt và quản lý thông qua một PID (Process ID - Mã định danh tiến trình) duy nhất.
- Tiến trình đại diện cho một đơn vị hoạt động trong hệ thống, chứa:
+ Mã chương trình
+ Vùng nhớ riêng
+ Ngăn xếp (stack), dữ liệu (data), và bộ đếm lệnh (program counter)
+ Các tài nguyên khác như file descriptor, biến môi trường, trạng thái CPU...
### Program(Chương trình)
- Program là một tập hợp các chỉ thị (instruction/code) được lưu trữ trong một file (thường ở định dạng nhị phân hoặc script).
- Program ở trạng thái tĩnh: chưa thực thi, chỉ nằm trên đĩa cứng.
- Khi một chương trình được thực thi, nó trở thành một process.
- Một chương trình có thể sinh ra nhiều tiến trình khác nhau, ví dụ: bạn mở 2 cửa sổ firefox thì sẽ có 2 process riêng biệt từ cùng một program.
### Process và Program khác nhau như thế nào?
So sánh nhanh
Tiêu chí	   |Program (Chương trình)	|Process (Tiến trình)
Trạng thái	   |Tĩnh (lưu trên đĩa) 	|Động (đang chạy trong bộ nhớ)
Lưu trữ ở đâu  |Ổ cứng	                |RAM và tài nguyên hệ thống
Định danh	   |Không có PID	        |Có PID duy nhất
Ví dụ	       |File /bin/ls	        |Khi bạn gõ ls và nó đang chạy
## 2. Command-line Arguments(Tham số dòng lệch)
- Command-line arguments là các giá trị bạn truyền vào khi chạy một chương trình từ dòng lệnh (terminal). Chúng cho phép bạn điều khiển hành vi của chương trình mà không cần sửa mã nguồn.
- Ví dụ: `./program_name arg1 arg2 arg3 ...`(file vidu.c)

## 3. Memory Layout
### Memory Layout(Trình bày bộ nhớ)
- Bộ nhớ (Memory) là nơi mà các tiến trình lưu trữ dữ liệu và chương trình của
- Bộ nhớ được chia thành các phần khác nhau, mỗi phần có chức năng riêng:
+ **Code Segment (CS)**(Text segment): lưu trữ mã chương trình (code) của tiến trình
+ **Data Segment (DS)**: lưu trữ dữ liệu (data) của tiến trình
+ **Stack Segment (SS)**: lưu trữ ngăn xếp (stack) của tiến trình
+ **Heap Segment (HS)**: lưu trữ vùng nhớ động (heap) của tiến trình
+ **Program Counter (PC)**: chỉ số bộ đếm lệnh (program counter) của tiến

| Thành phần       | Vai trò chính                                              |
| ---------------- | -------------------------------------------                |
| **Text Segment** | Lưu mã chương trình (chỉ đọc, chia sẻ được)                |
| **Data Segment** | Lưu biến toàn cục đã khởi tạo                              |
| **BSS Segment**  | Biến toàn cục và biến tĩnh chưa khởi tạo                   |
| **Heap**         | Cấp phát động trong lúc chạy chương trình                  |
| **Stack**        | Dùng cho lời gọi hàm, lưu biến cục bộ, tham số hàm, địa chỉ trả về… |
| **PC**           | Quản lý luồng thực thi                                     |

### initialized và uninitilized data segment
- khởi tạo tường minh thì được lưu trữ trong initi
- khởi tạo không tường minh thì được lưu trữ trong unniti
### Dùng công cụ như valgrind để kiểm tra bộ nhớ rò rỉ

## 4. Operations in Process 
🧩 1. Process Creation (Tạo tiến trình)
Hệ điều hành cho phép một tiến trình (cha) tạo ra tiến trình khác (con) thông qua system call như:

fork() (Unix/Linux)

CreateProcess() (Windows)

Cấu trúc cây tiến trình sẽ được hình thành (cha → con).

🧹 2. Process Termination (Kết thúc tiến trình)
Khi tiến trình hoàn thành công việc hoặc gặp lỗi, nó sẽ bị kết thúc bằng:

exit() – kết thúc bình thường.

kill() hoặc lỗi hệ thống – kết thúc bất thường.

Hệ điều hành sẽ thu hồi tài nguyên.
### System call fork
- fork() là một hệ thống gọi (system call) trong Unix/Linux, cho phép tạo ra một bản sao của một tiến trình hiện tại.
- Khi một tiến trình gọi fork(), hệ thống sẽ tạo ra một bản sao của tiến trình đó
- Bản sao này sẽ có cùng mã chương trình, dữ liệu và trạng thái như tiến trình ban đầu
- getpid in ra pid cảu tiến trình hiện tại
- getppid in ra pid của tiến trình cha hoặc 1 nếu tiến trình cha là tiến trình gốc
### System call exec
- exec() là một hệ thống gọi (system call) trong Unix/Linux, cho phép thay thế mã chương trình của một tiến trình bằng mã chương trình của một chương trình khác.
### System call exit(dừng bình thường)
- exit() là một hệ thống gọi (system call) trong Unix/Linux, cho phép một tiến trình kết thúc hoạt động và trở về trạng thái cuối cùng.
### System call wait
- wait() là một hệ thống gọi (system call) trong Unix/Linux, cho phép một tiến trình chờ đợi cho đến khi một tiến trình con kết thúc hoạt động.
- Trả về: PID của tiến trình con đã kết thúc.
### System call kill(dừng bất thường)
- kill() là một hệ thống gọi (system call) trong Unix/Linux, cho phép một tiến trình "giết" tiến trình mà còn có thể gửi nhiều loại tín hiệu khác nhau (như tạm dừng, tiếp tục, hoặc tín hiệu tùy chỉnh).
## 5. Orphant and Zombie Process
### Orphant Process
- Orphan process là tiến trình con vẫn còn đang chạy, nhưng tiến trình cha của nó đã kết thúc trước.
- Khi cha kết thúc mà không chờ con (wait()), con trở thành mồ côi. Lúc đó, tiến trình init (PID 1) hoặc systemd sẽ "nhận nuôi" tiến trình này để đảm bảo hệ thống vẫn quản lý được nó.
### Zombie Process
- Zombie process là một tiến trình con  đã kết thúc hoạt động nhưng vẫn còn tồn tại trong hệ thống vì cha của nó chưa gọi wait() để lấy PID của tiến trình con.
- Khi một tiến trình con kết thúc hoạt động, nó sẽ gửi một tín hiệu SIGCHLD
- "Cách để xóa một zombie process là:
→ Tiến trình cha phải gọi wait() hoặc waitpid() để thu nhận trạng thái của tiến trình con.
→ Nếu tiến trình cha không làm điều đó, ta có thể kill tiến trình cha. Sau đó, tiến trình zombie sẽ được tiến trình init (PID 1) nhận nuôi, và hệ thống sẽ tự động thu dọn zombie."
## 6. Assigsments
## 7. Kiến thức thêm
### 7.1. Process Scheduling
### 7.2. Process Synchronization
### 7.3. Process Communication
### 7.4. Creat Process
### 7.5. Process Termination