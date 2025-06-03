# Chạy Giả Lập Image Bằng QEMU với Yocto Project

Bài viết này hướng dẫn bạn từng bước thiết lập môi trường, tải mã nguồn, cấu hình và xây dựng image cho Yocto Project. Đồng thời, chúng ta cũng sẽ sử dụng QEMU để giả lập và kiểm tra image đã tạo.

# 1. Yêu Cầu Phần Cứng và Phần Mềm
1.1. Yêu cầu phần cứng
CPU: Tối thiểu 4 nhân (quad-core), ưu tiên tốc độ cao.

RAM: Tối thiểu 8GB (khuyến nghị 16GB).

Ổ cứng: Ít nhất 50GB trống (khuyến nghị SSD, có thể cần 100GB+).

## 1.2. Yêu cầu phần mềm
Hệ điều hành:

Ubuntu 20.04 LTS hoặc cao hơn

Debian 10/Buster hoặc mới hơn

Fedora, CentOS có thể dùng nhưng cần cấu hình thêm

## 1.3. Cấu hình tham khảo
OS: Ubuntu 22.04

RAM: 8GB

Storage: 100GB SSD

CPU: 4 nhân, 2 luồng @ 3.2GHz

# 2. Chuẩn Bị Môi Trường
## 2.1. Cài đặt các công cụ cần thiết
Trên Ubuntu/Debian
- sudo apt-get update
- sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib \
     build-essential chrpath socat cpio python python3 python3-pip python3-pexpect \
     xz-utils debianutils iputils-ping libsdl1.2-dev xterm vim
Trên Fedora
- sudo dnf install gawk make wget tar bzip2 gzip python3 unzip perl patch \
     diffutils diffstat git cpp gcc gcc-c++ glibc-devel texinfo chrpath \
     ccache perl-Data-Dumper perl-Text-ParseWords perl-Thread-Queue perl-bignum socat \
     python3-pexpect findutils which file cpio python python3-pip xz SDL-devel xterm
# 3. Tải Mã Nguồn Yocto Project
## 3.1. Clone mã nguồn
mkdir ~/yocto && cd ~/yocto
git clone git://git.yoctoproject.org/poky
## 3.2. Cấu trúc thư mục Poky
bitbake/: Công cụ build chính.

meta/: Layer core.

meta-poky/: Layer cấu hình mở rộng.

meta-yocto-bsp/: BSP cho phần cứng cụ thể.

scripts/, oe-init-build-env: Script thiết lập môi trường.

# 4. Xây Dựng Image Cho QEMU
## 4.1. Chuyển branch
cd ~/yocto/poky
git checkout dunfell

## 4.2. Khởi tạo môi trường
source oe-init-build-env
→ Tạo thư mục build/ chứa output và cấu hình.

## 4.3. Cấu hình build
### 4.3.1. local.conf
Tối ưu dung lượng ổ đĩa:
NHERIT += "rm_work"
Chọn hệ quản lý gói:

PACKAGE_CLASSES ?= "package_rpm"
Máy đích (QEMU x86-64):

MACHINE ?= "qemux86-64"
### 4.3.2. bblayers.conf
Ví dụ:

BBLAYERS ?= " \
  /home/aosp/yocto/poky/meta \
  /home/aosp/yocto/poky/meta-poky \
  /home/aosp/yocto/meta-openembedded/meta-oe \
  /home/aosp/yocto/meta-yocto-bsp \
"
## 4.4. Tiến hành build image

bitbake core-image-minimal
⏳ Lưu ý: Quá trình build lần đầu có thể mất vài giờ.

## 4.5. Chạy image bằng QEMU

runqemu qemux86-64 nographic
# 5. Kết Luận
Thông qua các bước trên, bạn đã biết cách:

✅ Thiết lập môi trường build Yocto
✅ Build image hệ điều hành nhúng
✅ Sử dụng QEMU để kiểm tra nhanh trước khi đưa lên thiết bị thật

Yocto Project là công cụ mạnh mẽ cho hệ thống nhúng và có thể tùy biến sâu theo yêu cầu riêng.

