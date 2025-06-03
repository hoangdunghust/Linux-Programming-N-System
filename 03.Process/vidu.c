#include <stdio.h>
#include <string.h>

void printHello() {
    printf("Hello Linux\n");
}

int main(int argc, char *argv[]) {
    printf("Tổng số tham số: %d\n", argc);

    if (argc < 2) {
        printf("Bạn cần truyền một tham số dòng lệnh (vidu hoặc vidu1)\n");
        return 1;
    }

    if (strcmp(argv[1], "vidu") == 0) {
        printf("Chương trình này được gọi là vidu\n");
    } else if (strcmp(argv[1], "vidu1") == 0) {
        printf("Chương trình này được gọi là vidu1\n");
    } else if (strcmp(argv[1], "hello") == 0) {
        printf("Chương trình này được gọi là hello\n");
        printHello();
    } else {
        printf("Chương trình này không được gọi là vidu hoặc vidu1\n");
    }

    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    return 0;
}
