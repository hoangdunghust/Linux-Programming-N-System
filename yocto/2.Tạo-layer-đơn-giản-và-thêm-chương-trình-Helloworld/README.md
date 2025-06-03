# Tạo Layer đơn giản và thêm chương trình HelloWorld trong Yocto

Trong bài viết này, chúng ta sẽ cùng tìm hiểu cách tạo một Layer Yocto mới và xây dựng ứng dụng HelloWorld. Đây là một hướng dẫn cơ bản nhưng thiết yếu, giúp bạn làm quen với cách tổ chức và tích hợp phần mềm vào hệ thống Yocto.

# 1. Tạo một Layer Yocto mới
## 1.1 Layer trong Yocto là gì?
Trong Yocto, layer là đơn vị tổ chức chứa các recipe, patch, và cấu hình cần thiết cho phần mềm hoặc phần cứng cụ thể. Mỗi layer thường phục vụ một chức năng độc lập: ví dụ như hỗ trợ phần cứng (meta-raspberrypi), phần mềm mở rộng (meta-openembedded) hoặc layer riêng của dự án.

## 1.2 Các bước tạo layer
### 1.2.1 Thiết lập môi trường
Truy cập thư mục Yocto (ví dụ poky) và khởi động môi trường build:

source oe-init-build-env
Kết quả:
/### Shell environment set up for builds. ###/
You can now run 'bitbake <target>'
### 1.2.2 Tạo layer mới
Sử dụng bitbake-layers:

bitbake-layers create-layer ../meta-devlinux
Kết quả:

Add your new layer with 'bitbake-layers add-layer ../meta-devlinux'
➡️ Thêm layer vào hệ thống:

bitbake-layers add-layer ../meta-devlinux
# 2. Thêm chương trình HelloWorld
## 2.1 Tạo recipe
Tạo thư mục chứa recipe:

cd meta-devlinux
mkdir -p recipes-apps/hello-world/files
Tạo file hello-world.bb trong recipes-apps/hello-world/ với nội dung:

DESCRIPTION = "Simple hello-world application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://hello-world.c"

S = "${WORKDIR}"

do_compile() {
    ${CC} hello-world.c ${LDFLAGS} -o hello-world
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 hello-world ${D}${bindir}
}
## 2.2 Tạo mã nguồn
Tạo file hello-world.c tại recipes-apps/hello-world/files/hello-world.c:

#include <stdio.h>

int main() {
    printf("Devlinux: hello world!\n");
    return 0;
}
## 2.3 Thêm chương trình vào image
Mở file build/conf/local.conf và thêm:

IMAGE_INSTALL_append = " hello-world"
Nếu dùng máy ảo QEMU cho kiến trúc x86-64, cấu hình:

MACHINE ?= "qemux86-64"
## 2.4 Build image
Chạy lệnh:


bitbake core-image-minimal
## 2.5 Chạy ứng dụng
Sau khi build xong, chạy máy ảo:

runqemu qemux86-64 nographic
Sau khi đăng nhập, chạy:


hello-world
Kết quả:


Devlinux: hello world!
# Kết luận
Bạn đã hoàn thành:

Tạo một layer Yocto mới (meta-devlinux)

Viết recipe cho ứng dụng HelloWorld

Tích hợp ứng dụng vào image

Build và chạy thành công trên QEMU