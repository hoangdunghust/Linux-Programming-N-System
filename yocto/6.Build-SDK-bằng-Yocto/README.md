# Hướng Dẫn Toàn Diện về SDK trong Yocto: Từ Cơ Bản đến Ứng Dụng
Yocto Project không chỉ là một công cụ mạnh mẽ để tạo ra các bản phân phối Linux tùy chỉnh cho hệ thống nhúng, mà còn cung cấp một Software Development Kit (SDK) giúp tăng tốc phát triển ứng dụng. Trong bài viết này, chúng ta sẽ cùng tìm hiểu cách xây dựng, cài đặt và sử dụng SDK trong Yocto một cách bài bản và hiệu quả.

## 1. SDK trong Yocto là gì?
SDK (Software Development Kit) là một tập hợp công cụ hỗ trợ các nhà phát triển viết và biên dịch ứng dụng dành riêng cho hệ điều hành được tạo bởi Yocto. Một SDK tiêu chuẩn bao gồm:

- **Cross-Development Toolchain**: Trình biên dịch chéo cho phép biên dịch ứng dụng trên máy host (PC) nhưng chạy trên thiết bị target (nhúng).

- **Thư viện và Header Files**: Các thành phần cần thiết để phát triển ứng dụng.

- **Scripts thiết lập môi trường**: Thiết lập nhanh môi trường phát triển nhất quán.

# 2. Các Cách Xây Dựng SDK trong Yocto
## 2.1. Tích Hợp SDK vào Hệ Điều Hành (Image)
Đây là cách đơn giản nhất để sử dụng SDK: tích hợp trực tiếp công cụ phát triển vào hệ thống target.

- Bước 1: Mở file build/conf/local.conf và thêm dòng sau:
EXTRA_IMAGE_FEATURES ?= "tools-sdk"
- Bước 2: Build lại image:
bitbake core-image-minimal
- Kết quả là bạn có thể phát triển ứng dụng trực tiếp trên thiết bị nhúng (target), với các công cụ như gcc, make, gdb, v.v.

## 2.2. Tạo SDK Độc Lập cho Máy Host
- Đây là cách phổ biến và chuyên nghiệp hơn, giúp bạn phát triển ứng dụng trên máy host mà không cần can thiệp trực tiếp vào thiết bị target.

### a. Standard SDK
Tạo SDK tiêu chuẩn với lệnh:
bitbake core-image-minimal -c populate_sdk
Sau khi hoàn tất, file .sh cài đặt SDK sẽ xuất hiện trong:
build/tmp/deploy/sdk/
Ví dụ:
poky-glibc-x86_64-core-image-minimal-arm1176jzfshf-vfp-raspberrypi0-wifi-toolchain-3.1.33.sh
### b. Extensible SDK (eSDK)
Để có thêm các công cụ như devtool phục vụ phát triển và gỡ lỗi nhanh, sử dụng eSDK:
bitbake core-image-minimal -c populate_sdk_ext
# 3. Cài Đặt và Thiết Lập Môi Trường SDK
## 3.1. Cài Đặt SDK
Chạy script .sh để cài SDK trên máy host:
./poky-glibc-x86_64-core-image-minimal-<target>.sh

Bạn có thể chọn thư mục cài đặt, mặc định là /opt/poky/.

## 3.2. Thiết Lập Môi Trường Phát Triển
Sau khi cài xong, hãy thiết lập môi trường:
source /opt/poky/3.1.33/environment-setup-arm1176jzfshf-vfp-poky-linux-gnueabi
Lệnh trên sẽ thiết lập các biến môi trường như CC, CXX, PATH, v.v. để sử dụng toolchain và thư viện phù hợp.

Kiểm tra:
echo $CC
Bạn sẽ thấy trình biên dịch chéo như arm-poky-linux-gnueabi-gcc.

# 4. Thực Hành: Biên Dịch và Chạy Ứng Dụng Cơ Bản với SDK
## 4.1. Tạo Mã Nguồn
Tạo file hello_SDK.c:
#include <stdio.h>

int main() {
    printf("Devlinux: hello SDK!\n");
    return 0;
}
## 4.2. Biên Dịch với SDK
**$CC -o hello_SDK_app hello_SDK.c**
## 4.3. Chạy Trên Thiết Bị Target
Sử dụng scp để gửi file:
scp hello_SDK_app root@192.168.7.2:~/
Trên thiết bị target:
./hello_SDK_app
Kết quả:
Devlinux: hello SDK!
# 5. Lợi Ích Khi Sử Dụng SDK trong Yocto
✅ Phát triển nhanh chóng: Không cần rebuild image mỗi khi cập nhật ứng dụng.
✅ Môi trường thống nhất: Giống hệt môi trường target nên giảm lỗi biên dịch/runtime.
✅ Tiện lợi: Phát triển trực tiếp trên host bằng các công cụ quen thuộc như VSCode, Eclipse.
✅ Tối ưu tài nguyên: Không cần cài công cụ nặng trên thiết bị nhúng.

# 6. Kết Luận
Việc sử dụng SDK trong Yocto là một trong những bước đi thông minh giúp bạn tách biệt giữa phát triển ứng dụng và xây dựng hệ thống, từ đó tiết kiệm thời gian và nâng cao hiệu quả làm việc. Đây là công cụ không thể thiếu cho bất kỳ nhà phát triển hệ thống nhúng nào.