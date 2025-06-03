# Các thuật ngữ quan trọng trong Yocto
Bài viết này giúp bạn mới bắt đầu với Yocto hiểu rõ về 4 thành phần cốt lõi nhất định phải nắm: Image, Machine, Distro, Local.conf.

# 1. Image – Công thức tạo Root File System (RFS)
Image là một recipe mô tả **những gì sẽ có trong hệ thống gốc** (RFS).

Ví dụ: core-image-minimal.bb – image tối giản để khởi động.

Các biến quan trọng:

IMAGE_INSTALL: Gói phần mềm cần cài.

CORE_IMAGE_EXTRA_INSTALL: Thêm gói tùy chỉnh.

inherit core-image: Kế thừa class xử lý image.

IMAGE_ROOTFS_SIZE: Dung lượng rootfs.

IMAGE_ROOTFS_EXTRA_SPACE_append: Thêm dung lượng dựa vào DISTRO_FEATURES.

# 2. Machine – Mô tả phần cứng mục tiêu
Machine **file định nghĩa phần cứng**(như CPU, driver, kernel, bootloader, ...).

Ví dụ: qemux86.conf cho QEMU x86.

Các dòng quan trọng:

PREFERRED_PROVIDER_virtual/xserver: Chọn trình cung cấp xserver.

UBOOT_MACHINE: File cấu hình cho U-Boot.

KERNEL_IMAGETYPE: Kiểu image kernel (bzImage, zImage, ...).

MACHINE_FEATURES: Tính năng phần cứng (x86, PCI, ...).

SERIAL_CONSOLES: Cổng serial dùng cho debug.

# 3. Distro – Phân phối phần mềm tùy chỉnh
Distro là một bản phân phối (distribution) chứa tất cả cấu hình phần mềm, kernel, cấu trúc build,...

Mặc định là poky (có sẵn trong Yocto).

File ví dụ: poky.conf

Các biến phổ biến:

DISTRO: Tên của bản distro.

DISTRO_FEATURES: Các tính năng tích hợp mặc định (opengl, wayland, multiarch, ...).

POKY_DEFAULT_DISTRO_FEATURES: Tập hợp mặc định nếu không override.

SDK_NAME, SDK_VENDOR: Liên quan đến công cụ SDK xuất ra.

INHERIT: Kế thừa các class cấu hình khác như poky-sanity, uninative, security_flags,...

# 4. local.conf – Cấu hình cho từng môi trường build cụ thể
Nằm tại: build/conf/local.conf

Tùy chỉnh cho từng phiên bản build riêng biệt.

Các biến quan trọng:

MACHINE: Chỉ định target board.

DISTRO: Chọn bản phân phối (thường là poky).

IMAGE_FSTYPES: Định dạng file output (ext4, wic, tar.gz, ...).

BB_NUMBER_THREADS: Số luồng BitBake.

PARALLEL_MAKE: Thread make sử dụng.

TMPDIR: Thư mục lưu output tạm thời trong quá trình build.

# Tổng kết
Thành phần      Vai trò chính
Image	        Định nghĩa cấu trúc hệ thống gốc
Machine	        Mô tả phần cứng mục tiêu
Distro	        Bản phân phối tích hợp các thiết lập hệ điều hành
local.conf	    Cấu hình cục bộ cho môi trường build cụ thể