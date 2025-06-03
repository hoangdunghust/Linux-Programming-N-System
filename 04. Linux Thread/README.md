# What is Thread

✅ Các loại Thread:
User-level Threads (Threads cấp người dùng):
Được quản lý bởi thư viện thread bên ngoài hệ điều hành.
Quản lý bởi ứng dụng hoặc thư viện, không được hệ điều hành quản lý trực tiếp.
Kernel-level Threads (Threads cấp kernel):
Được quản lý trực tiếp bởi hệ điều hành.
Hệ điều hành quản lý việc lập lịch và phân phối tài nguyên cho từng thread.
Hybrid Threads:
Kết hợp giữa quản lý ở cấp độ người dùng và kernel. Một số thread được quản lý bởi người dùng, nhưng những thread quan trọng sẽ được hệ điều hành quản lý.

# Mục lục

1. [Giới thiệu về Thread(introduction)](#thread)
2. [Thread vs. Process](#thread-vs-process)
3. [Cấu trúc của một Thread](#cấu-trúc-của-một-thread)
4. [Hoạt động trên Thread](#hoạt-động-của-thread)
5. [Quản lý trên Thread](#quản-ly-thread)
6. [Đồng bộ hóa trên Thread](#đồng-bộ-hóa-thread)
7. [Các loại Thread](#các-loại-thread)

# Chi tiết

## 1. Giới thiệu về Thread(introduction)

### Định nghĩa:

- Thread là một đơn vị thực thi cơ bản trong một tiến trình. Một tiến trình có thể chứa nhiều thread và tất cả các thread trong cùng một tiến trình sẽ chia sẻ cùng một bộ nhớ (memory space) và tài nguyên (ví dụ: tệp tin, kết nối mạng).
- Hiểu đơn giản nó là luồng

### Cấu trúc của một tiến trình:

- Một tiến trình có thể chứa nhiều thread, mỗi thread có thể thực thi một phần công việc riêng biệt mà không cần phải tạo ra một tiến trình hoàn toàn mới.
- Thread có thể xem như là tiến trình nhẹ (lightweight process) vì chúng chia sẻ bộ nhớ và tài nguyên với nhau.
- Nằm trong vùng stack

### Ưu điểm của việc sử dụng Threads:

- Chia sẻ bộ nhớ: Các thread trong cùng một tiến trình chia sẻ bộ nhớ và tài nguyên, giúp tiết kiệm bộ nhớ.
- Thực thi song song: Nhiều thread có thể thực thi song song trên nhiều core của CPU, giúp tăng hiệu suất.
- Giao tiếp dễ dàng: Threads trong cùng một tiến trình có thể giao tiếp trực tiếp với nhau, không cần cơ chế IPC phức tạp.

### Nhược điểm:

- Deadlock: Nếu các thread không đồng bộ đúng cách, có thể dẫn đến deadlock, nơi các thread chờ nhau vô hạn.
- Chia sẻ tài nguyên: Vì các thread chia sẻ bộ nhớ, một thread có thể thay đổi dữ liệu của một thread khác, gây lỗi.
- Khó quản lý: Quản lý nhiều thread trong một ứng dụng phức tạp có thể làm tăng sự phức tạp của mã nguồn.

### Context Switching:

- Khi hệ điều hành chuyển từ một thread sang thread khác, nó phải lưu trữ trạng thái của thread hiện tại và tải trạng thái của thread mới. Điều này có thể tốn thời gian và làm giảm hiệu suất.
- Context switching có thể xảy ra khi một thread bị dừng lại hoặc khi một thread mới được tạo ra
- Context switching dgl bối cảnh chuyển đổi giữa các thread

## 2. Thread vs. Process

| Tiến trình                                 | Thread                                                                                            |
| ------------------------------------------ | ------------------------------------------------------------------------------------------------- | ----------- |
| Mất nhiều thời gian context switching hơn  | Mất ít thời gian context switching                                                                |
| Tiến trình có thể có một hoặc nhiều thread | Mỗi tiến trình chứa ít nhất một thread                                                            |
| Mỗi tiến trình có không gian bộ nhớ riêng  | Các thread trong tiến trình chia sẻ bộ nhớ và tài nguyên                                          |
| có thể chia sẻ bộ nhớ nhưng khó            |
| Tiến trình tốn nhiều tài nguyên hơn        | Thread nhẹ hơn, tạo và kết thúc nhanh hơn                                                         |
| Tiến trình độc lập với nhau                | Các thread trong cùng tiến trình có thể giao tiếp dễ dàng nhưng 1 thread có thể ảnh hưởng đến các | thread khác |

## 3. Cấu trúc của một Thread

Thread (luồng) là đơn vị nhỏ nhất của CPU có thể thực thi độc lập trong một tiến trình. Trong môi trường pthread (POSIX Threads), thread có một số cấu trúc và thuộc tính đặc trưng:

✅ 1. Thread ID (pthread_t)
Mỗi thread có một ID duy nhất được đại diện bằng kiểu pthread_t.

Được hệ điều hành cấp để quản lý thread.

Lấy ID thread hiện tại:

c
Copy
Edit
pthread_t tid = pthread_self();
✅ 2. Hàm xử lý (Thread Routine)
Là một hàm có kiểu void* và tham số đầu vào là void*.

Đây là nơi thread thực hiện công việc:

c
Copy
Edit
void* myThread(void* arg) {
// Xử lý công việc tại đây
pthread_exit(NULL);
}
✅ 3. Tham số truyền vào
Thread có thể nhận tham số bất kỳ, miễn là ép về kiểu (void\*).

Ví dụ truyền struct:

typedef struct {
int id;
char name[30];
} Student;

Student s = {1, "Nguyen Van A"};
pthread_create(&tid, NULL, myThread, (void\*)&s);
✅ 4. Trạng thái Thread
Một thread có thể có các trạng thái: running, waiting, canceled, terminated.

Khi gọi pthread_exit() hoặc thread kết thúc hàm, nó sẽ terminated.

✅ 5. Trả về kết quả
Thread có thể trả lại kết quả qua pthread_exit() hoặc thông qua con trỏ khi dùng pthread_join():

void* myThread(void* arg) {
int* result = malloc(sizeof(int));
*result = 42;
pthread_exit((void\*) result);
}

void* ret;
pthread_join(tid, &ret);
printf("Kết quả thread: %d\n", *(int\*)ret);
✅ 6. Đồng bộ hóa (Synchronization)
Để tránh race condition khi nhiều thread truy cập vùng nhớ chung, bạn cần dùng mutex:

pthread_mutex_t lock;
pthread_mutex_init(&lock, NULL);

pthread_mutex_lock(&lock);
// critical section
pthread_mutex_unlock(&lock);
Tổng kết:
Thành phần Mô tả
pthread_t ID của thread
Thread function Hàm thực hiện công việc
pthread_create Tạo thread
pthread_exit Kết thúc thread
pthread_join Chờ thread kết thúc
pthread_cancel Huỷ thread
pthread_mutex Đồng bộ giữa các thread

## 4. Hoạt động của Thread

### 1. Thread ID (ID của Thread):

Mỗi thread có một ID duy nhất được hệ điều hành cấp phát.
Dùng để nhận diện và quản lý thread.
Các hàm liên quan:

- pthread_self() → trả về ID của thread hiện tại.
- pthread_equal(pthread_t t1, pthread_t t2) → so sánh hai thread:

* Trả về 0 nếu hai thread khác nhau.
* Trả về khác 0 nếu hai thread giống nhau.

### 2. Tạo Thread (Creating a Thread):

Hàm: pthread_create()
Cú pháp:
` int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);`
thread: con trỏ đến biến chứa ID thread mới.
attr: thuộc tính thread (NULL nếu dùng mặc định).
start_routine: hàm mà thread sẽ thực thi.
arg: tham số truyền vào cho hàm đó (có thể là NULL nếu không cần).
Trả về:
0 nếu tạo thành công.
khác 0 nếu tạo thất bại.

### 3. Kết thúc Thread (Terminating a Thread):

Có 3 cách kết thúc một thread:

- Thread thực hiện xong hàm start_routine → tự động kết thúc.
- Gọi pthread_exit(void \*retval) từ trong thread → kết thúc và trả giá trị.
- Thread chính kết thúc và gọi pthread_join() hoặc exit() → chờ thread con kết thúc.
- Lưu ý quan trọng:

pthread_exit() chỉ kết thúc thread hiện tại, không kết thúc toàn bộ tiến trình.
Khi thread chính (main thread) kết thúc, nếu không gọi pthread_join(), các thread khác có thể bị bỏ dở.
Ví dụ minh họa: thread.c
Huỷ thread — pthread_cancel()

pthread_cancel(thread_id);
Gửi yêu cầu huỷ thread. Tuy nhiên:

Thread chỉ bị huỷ nếu nó ở trạng thái cancelable và responds to cancellation points (như sleep(), read(), pthread_testcancel(),…).

### 4. So sánh thread — pthread_equal()

if (pthread_equal(tid1, tid2)) {
// Hai thread giống nhau
}

### 5. Lấy ID của thread hiện tại — pthread_self()

pthread_t tid = pthread_self();

### 6. Đồng bộ thread — Dùng mutex (pthread_mutex)

pthread_mutex_t lock;
pthread_mutex_init(&lock, NULL);

pthread_mutex_lock(&lock);
// Code bảo vệ (critical section)
pthread_mutex_unlock(&lock);
| Thuộc tính | `pthread_cancel()` | `pthread_exit()` |
| **Mục đích** | Gửi yêu cầu **hủy một thread khác** | **Kết thúc chính thread hiện tại** |
| **Chủ động / Bị động** | **Bị động** (thread bị hủy bởi thread khác) | **Chủ động** (thread tự thoát) |
| **Thread nào gọi?** | Một thread **gọi để hủy thread khác** | Thread **tự gọi để thoát** |
| **Xử lý bên trong** | Phụ thuộc vào **trạng thái hủy (cancelability)** của thread bị hủy | Luôn **thoát ngay lập tức** |
| **Cần điểm hủy (cancel point)** | Có, thread chỉ dừng tại **cancel point** | Không cần điểm nào cả |
| **Trả giá trị về main thread?** | Không (trừ khi xử lý phức tạp) | Có thể trả giá trị với `pthread_exit((void*)result)`|
| **Dừng đột ngột?** | Có thể không dừng nếu thread từ chối hủy | Luôn dừng |
| **Ví dụ điển hình** | Dừng thread con từ thread chính sau khi timeout | Kết thúc thread sau khi hoàn thành công việc|

### pthread_join() hoặc pthread_detach()

pthread_join() là một hàm dùng để đợi một thread kết thúc, nghĩa là thread hiện tại sẽ bị chặn (block) cho đến khi thread kia hoàn thành công việc.
` int pthread_join(pthread_t thread, void **retval);`
thread: ID của thread cần chờ.
retval: con trỏ tới con trỏ (void\*\*) để nhận giá trị trả về từ pthread_exit() của thread kia. Nếu không cần, truyền NULL.

- pthread_detach() là một hàm dùng để tách một thread khỏi tiến trình hiện tại, nghĩa là thread đó sẽ tự động kết thúc khi tiến trình kết thúc.

## 5. Quản lí thread

### 1. related concept(Khái niệm liên quan)

- Atomic/non-Atomic : Atomic là các lệnh không thể bị ngắt giữa, non-atomic là cnhuywngx thao tác có thể bị dán đoạn ví dụ như `x = 5 ; y = 10;` là 2 lệnh non-Atomic, còn `x = 5 + y` là 1 lệnh Atomic.
- Critical Section (Khu vực bảo vệ/ vùng trọng yếu): Là một phần của chương trình được thực hiện/ truy cập bởi một thread mà không bị ảnh hưởng bởi các thread khác.
- Share Resource (Sử dụng chung tài nguyên): Là tài nguyên được nhiều thread sử dụng chung, cần bảo vệ để tránh xung đột

## 6. Thread sync - Mutex lock(đồng bộ hóa)
- là kĩ thuật dùng để chỉ một đối tượng được sử dụng trong 1 thời điểm
- Mutex (Mutex Lock): Là một biến dùng để đồng bộ các thread, nó có thể được xem như một "chìa khóa" dùng để mở và đóng một vùng code.

pthread_mutex_t lock; // Khai báo mutex

pthread_mutex_init(&lock, NULL); // Khởi tạo mutex

pthread_mutex_lock(&lock); // Mở khóa mutex (vào vùng bảo vệ)
// Critical section
pthread_mutex_unlock(&lock); // Đóng khóa mutex (rời vùng bảo vệ)

pthread_mutex_destroy(&lock); // Hủy mutex khi không cần nữa

- có thể khởi tạo tĩnh hoặc động
- khi một khóa trong trạng thái unlock thì một thread có thể gọi dc nó, còn nếu đang dc sử dụng thì phải chờ
- trường hợp khóa chết khi hai thread chờ hai khóa của nhau thread1 chờ khóa 2 và người lại
## 7.conditional variable

## bài tập 
