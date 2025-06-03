# 1. Package Dependencies (Phụ thuộc gói)
 là các yêu cầu cần thiết để một gói hoạt động bình thường
Trong Yocto, có hai loại phụ thuộc chính:
Build time dependencies: Các phụ thuộc cần thiết trong quá trình build.
Run time dependencies: Các phụ thuộc cần thiết khi package đang chạy.
## 1.1. Build-time Dependencies
- Ý nghĩa: Là các gói, thư viện cần thiết trong quá trình biên dịch (compile).
 Trong Yocto, biến DEPENDS được sử dụng để chỉ định các gói hoặc thư viện cần thiết cho quá trình này.
Khai báo bằng biến: DEPENDS = "tên-gói"
### Ví dụ:
Chương trình depend_buildtime.c sử dụng libcurl ⇒ cần DEPENDS = "curl" để có header và lib khi build.

🔧 Nếu không khai báo, khi build sẽ lỗi:

fatal error: curl/curl.h: No such file or directory
## 1.2. Run-time Dependencies
Ý nghĩa: Là các thành phần cần thiết khi chương trình chạy.

Khai báo bằng biến: RDEPENDS_${PN} = "bash"
### Ví dụ:

Chương trình depend_runtime.c sử dụng system("bash -c ...") ⇒ cần bash ở runtime.

Nếu không khai báo ⇒ chạy lỗi: sh: bash: not found.

🔧 Cách xử lý:

Thêm RDEPENDS_${PN} = "bash" trong recipe .bb

Hoặc thêm vào image:

IMAGE_INSTALL_append = " bash"
# 2. Package Splitting (Phân chia gói)
## Ý tưởng
Chia một gói chính thành nhiều gói con.

Giúp tối ưu image:

Giảm kích thước

Dễ cập nhật

Linh hoạt chọn phần nào cần cài

## Biến sử dụng:
PACKAGES: liệt kê các package con, ví dụ:
PACKAGES = "${PN} ${PN}-dev ${PN}-runtime"
FILES_${PN}: chỉ định file nào thuộc gói nào.
FILES_${PN} = "${bindir}/package_split"
FILES_${PN}-runtime = "${bindir}/depend_runtime"
FILES_${PN}-dev = "${bindir}/depend_buildtime"
## Lợi ích thực tế:
Bạn có thể chỉ tích hợp phần runtime vào image chính, giữ phần build/dev bên ngoài hoặc cài động khi cần.

# Tổng kết quy trình khi dùng Yocto để quản lý phụ thuộc và chia package:
Tạo recipe .bb chuẩn.

**Xác định phụ thuộc:**

DEPENDS cho build

RDEPENDS_${PN} cho runtime

Cấu hình chia nhỏ package nếu cần:

PACKAGES

FILES_${PN}, FILES_${PN}-something

Build và kiểm tra bằng QEMU hoặc thiết bị thật.

Tối ưu image bằng cách chỉnh IMAGE_INSTALL trong local.conf.
**Package Dependencies** đảm bảo các gói hoặc thư viện cần thiết được tích hợp đầy đủ trong quá trình build và runtime. Việc sử dụng đúng các biến như DEPENDS và RDEPENDS giúp hệ thống hoạt động ổn định và tránh các lỗi không mong muốn.
**Package Splitting** cho phép chia nhỏ một package thành các phần riêng biệt, giúp kiểm soát tốt hơn những gì được cài đặt vào hệ thống. Điều này đặc biệt hữu ích khi cần tối ưu hóa dung lượng hoặc quản lý các phần của ứng dụng một cách độc lập.