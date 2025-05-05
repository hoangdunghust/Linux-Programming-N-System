# Tên chương trình và file nguồn
TARGETS = bt1 bt2 bt3
CC = gcc
CFLAGS = -Wall

# Quy tắc mặc định: build tất cả
all: $(TARGETS)

bt1: bt1_append_seek.c
	$(CC) $(CFLAGS) -o bt1 bt1_append_seek.c

bt2: bt2_rw.c
	$(CC) $(CFLAGS) -o bt2 bt2_rw.c

bt3: bt3_stat.c
	$(CC) $(CFLAGS) -o bt3 bt3_stat.c

# Quy tắc dọn dẹp: xóa file thực thi
clean:
	rm -f $(TARGETS)
