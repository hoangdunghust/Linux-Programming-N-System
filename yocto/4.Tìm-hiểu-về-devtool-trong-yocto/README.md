# Devtool trong Yocto là gì?
- devtool là một tiện ích dòng lệnh mạnh mẽ của Yocto Project giúp đơn giản hóa việc phát triển, kiểm thử và tích hợp phần mềm bằng cách thao tác với các recipe. Thay vì phải chỉnh sửa thủ công rất nhiều file và cấu hình, Devtool cung cấp một workflow linh hoạt và nhanh chóng.

# Các chức năng chính của Devtool
Lệnh	                  Mô tả
devtool add	              Tạo mới recipe từ source code (local/git).
devtool modify	          Lấy source code từ recipe vào workspace để sửa.
devtool build	          Biên dịch recipe ngay trong workspace.
devtool deploy-target	  Triển khai gói đã build lên máy QEMU/device qua SSH.
devtool finish	          Di chuyển recipe từ workspace sang layer chính thức.
devtool reset	          Xóa recipe khỏi workspace (khôi phục trạng thái ban đầu).

# Chi tiết các bước sử dụng Devtool
## 1. Khởi tạo môi trường Yocto
source oe-init-build-env
## 2. Tạo recipe mới từ GitHub (lệnh devtool add)
devtool add hello-devtool https://github.com/DevLinux097/Yocto-For-Dummies.git --srcbranch custom-devtool
➡️ Sau khi thực hiện, Yocto tạo ra thư mục workspace/ chứa:

sources/: Source code lấy từ Git

recipes/: File .bb định nghĩa cách build

appends/, conf/: dùng trong các chỉnh sửa sau này

## 3. Build recipe (lệnh devtool build)
Sau khi chỉnh sửa file .bb để thêm lệnh biên dịch và cài đặt:
devtool build hello-devtool
Ví dụ lệnh biên dịch trong file .bb:
do_compile() {
    ${CC} ${S}/hello-devtool.c ${LDFLAGS} -o ${S}/hello-devtool
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/hello-devtool ${D}${bindir}
}
## 4. Deploy recipe sang máy QEMU (lệnh devtool deploy-target)
✅ Yêu cầu: QEMU hỗ trợ SSH (phải cài openssh vào image)
devtool deploy-target hello-devtool root@192.168.7.2
➡️ Kiểm tra:
/usr/bin/hello-devtool
# 5. Hoàn tất recipe (lệnh devtool finish)
Khi recipe đã ổn định, ta đưa nó vào layer cụ thể:
devtool finish -f hello-devtool ../meta-devlinux/recipes-apps/
➡️ Recipe hello-devtool_git.bb sẽ được copy vào layer meta-devlinux.

# 6. Chỉnh sửa source code của recipe (lệnh devtool modify)
devtool modify hello-devtool
➡️ Devtool sẽ copy source code từ layer chính thức vào workspace/sources/ để bạn chỉnh sửa.
Sau đó, bạn có thể:

devtool build hello-devtool lại

devtool reset hello-devtool để hủy các thay đổi

# Lợi ích khi dùng Devtool
Không ảnh hưởng đến layer chính thức khi đang phát triển

Hỗ trợ workflow theo kiểu agile: viết -> sửa -> test nhanh chóng

Có thể build/deploy độc lập từng gói phần mềm

Dễ rollback hoặc xóa bỏ khi không cần thiết

# Kết luận
Devtool là một công cụ cực kỳ hữu ích với những ai đang phát triển phần mềm hoặc tùy chỉnh hệ thống embedded với Yocto. Nó giúp tăng tốc đáng kể quá trình phát triển bằng cách tách biệt các thay đổi và cho phép kiểm thử linh hoạt trước khi tích hợp vào hệ thống sản phẩm cuối cùng.

