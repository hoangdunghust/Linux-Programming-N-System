1. Giới thiệu chung về IPC (Inter-Process Communication)
1.1. Khái niệm về IPC
IPC (Inter-Process Communication) – Giao tiếp liên tiến trình – là một cơ chế quan trọng trong hệ điều hành và lập trình hệ thống. IPC Semaphore được sử dụng để đồng bộ hóa truy cập vào tài nguyên chia sẻ giữa các tiến trình (process) và luồng (thread).

Semaphore là một biến đồng bộ được sử dụng để đếm số lượng tài nguyên có sẵn, giúp quản lý và bảo vệ tài nguyên chia sẻ, tránh xung đột và đảm bảo an toàn dữ liệu.

1.2. Tại sao cần IPC?
Đảm bảo an toàn và hiệu suất của hệ thống.

Giúp đồng bộ hóa truy cập giữa các tiến trình/luồng khi dùng chung tài nguyên.

Tránh tình trạng race condition, deadlock nếu kiểm soát tốt.

1.3. Các phương pháp IPC phổ biến
Pipe

Message Queue

Shared Memory

Semaphore

1.4. Các loại Semaphore
POSIX Semaphore

System V Semaphore

2. POSIX Semaphore
2.1. Khái niệm
POSIX Semaphore là loại semaphore tuân theo chuẩn POSIX (Portable Operating System Interface) – giao diện hệ điều hành chuẩn hóa.

Được cung cấp bởi thư viện pthread hoặc semaphore.h.

Gồm hai loại:

Named semaphore – có tên định danh, chia sẻ giữa các tiến trình.

Unnamed semaphore – không có tên, chia sẻ trong cùng một tiến trình hoặc giữa các thread.

3. Các thao tác trên Semaphore
3.1. Nguyên lý hoạt động
Khi một tiến trình cần truy cập vào tài nguyên được bảo vệ bởi semaphore:

Nếu semaphore > 0 → giảm giá trị (sem_wait) và truy cập tài nguyên.

Nếu semaphore = 0 → tiến trình bị chặn cho đến khi semaphore > 0.

Semaphore là một số nguyên được quản lý bởi kernel, không bao giờ nhỏ hơn 0.

3.2. Các hàm POSIX chính
Hàm	Mô tả
sem_init()	Khởi tạo unnamed semaphore
sem_wait()	Giảm giá trị semaphore; nếu = 0 thì block tiến trình
sem_post()	Tăng giá trị semaphore; đánh thức tiến trình đang chờ
sem_getvalue()	Lấy giá trị hiện tại của semaphore
sem_trywait()	Giống sem_wait nhưng không chặn nếu không thể giảm
sem_timedwait()	Chờ có timeout

4. Named Semaphore
4.1. Mở semaphore
c
Copy
Edit
sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
name: tên định danh (vd: "/mysem")

oflag: cờ mở semaphore (O_CREAT, O_EXCL, ...)

mode: quyền truy cập (vd: 0666)

value: giá trị khởi tạo

4.2. Gỡ bỏ semaphore
c
Copy
Edit
int sem_unlink(const char *name);
→ Dùng để xóa semaphore khỏi hệ thống.

5. Semaphore trong IPC (Liên tiến trình)
5.1. Sự khác biệt
Thread dùng chung địa chỉ bộ nhớ → có thể dùng unnamed semaphore.

Process cần dùng named semaphore hoặc semaphore nằm trong shared memory.

5.2. Ứng dụng semaphore trong đồng bộ tiến trình
Bảo vệ truy cập vùng nhớ chung (shared memory)

Điều phối thứ tự thực hiện giữa các tiến trình

Quản lý số lượng tiến trình truy cập tài nguyên hữu hạn

6. Triển khai semaphore trong Linux/Unix
6.1. System V Semaphore (ít dùng hơn POSIX)
Dùng các hàm:

semget() – tạo/bắt đầu nhóm semaphore

semctl() – điều khiển semaphore

semop() – thực hiện thao tác trên semaphore

6.2. Lưu ý
semget() cần key định danh semaphore set

semop() truyền mảng thao tác (P/V)

7. Ví dụ thực tế
Producer – Consumer Problem

Reader – Writer Problem

Dining Philosophers Problem

→ Dùng semaphore để tránh race condition và đảm bảo đồng bộ hóa logic.

8. Ưu điểm và nhược điểm
Ưu điểm:
Đơn giản, hiệu quả

Hạn chế race condition

Hệ điều hành hỗ trợ mạnh mẽ

Nhược điểm:
Dễ gây deadlock nếu sử dụng sai

Khó debug

Không thân thiện như các cơ chế mới như Mutex/Condition Variable trong multi-thread

9. So sánh với các cơ chế đồng bộ khác
Cơ chế	Phạm vi áp dụng	Ghi chú
Semaphore	Process & Thread	Đồng bộ hóa tài nguyên
Mutex	Thread (multi-thread)	Dễ dùng hơn cho thread
Monitor	OOP-based	Java synchronized block
Condition Variable	Kết hợp với Mutex	Linh hoạt, có wait/signal

10. Kết luận
Semaphore là một công cụ mạnh mẽ trong IPC để quản lý tài nguyên chia sẻ và điều phối tiến trình.

Việc hiểu và sử dụng đúng semaphore giúp tránh xung đột, nâng cao hiệu suất và độ tin cậy của chương trình.

Nên lựa chọn loại semaphore (POSIX hay System V) và kiểu semaphore (named hay unnamed) tùy theo mục đích sử dụng.

Trong tương lai, nên học thêm về các cơ chế đồng bộ hiện đại để phát triển hệ thống đa tiến trình và đa luồng hiệu quả.

11. so sánh mutex và semaphore
🔐 Mutex
Phạm vi: Đồng bộ hoạt động giữa các thread trong cùng một tiến trình.

Cơ chế hoạt động:
Một thread gọi pthread_mutex_lock() thì chính thread đó phải gọi pthread_mutex_unlock() để giải phóng.

Số lượng thread giữ Mutex tại một thời điểm: 1

Chỉ dùng trong nội bộ tiến trình (không dùng được giữa các process).

Có khái niệm sở hữu (ownership) → chỉ thread giữ mutex mới được mở khóa.

Thường dùng để bảo vệ vùng tài nguyên chỉ cho 1 thread truy cập tại một thời điểm.

🚦 Semaphore
Phạm vi: Đồng bộ hoạt động giữa các thread và cả các process.

Cơ chế hoạt động:
Một thread/process A gọi sem_post() thì bất kỳ thread/process nào khác đều có thể gọi sem_wait() (và ngược lại).

Số lượng thread/process giữ semaphore tại một thời điểm: > 1 nếu semaphore kiểu đếm.

Không có khái niệm sở hữu (ownership) → bất kỳ ai cũng có thể post hoặc wait.

🧮 Loại Semaphore
Binary Semaphore:

Giá trị: 0 hoặc 1

Tương tự mutex, nhưng không có sở hữu

Counting Semaphore:

Giá trị: >= 1

Cho phép nhiều thread cùng truy cập tài nguyên theo giới hạn định sẵn

🆚 So sánh tóm tắt
Tiêu chí	                 Mutex	                          Semaphore 
Loại	                     Nhị phân (binary)	              Nhị phân và đếm được
Số lượng giữ cùng lúc        1 thread	                      Nhiều thread/process
Phạm vi sử dụng	             Thread trong 1 process  	      Thread hoặc giữa các process
Sở hữu	                     Có	                              Không
Giải phóng (unlock/post)	 Chỉ thread giữ mutex mới unlock  Bất kỳ thread/process nào cũng có thể
