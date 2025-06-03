#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// Khai báo kiểu struct Student
typedef struct {
    int id;
    char name[30];
} Student;

// Hàm mà thread sẽ chạy
void* printStudentInfo(void* arg) {
    Student* s = (Student*)arg;  // Ép kiểu về Student*
    printf("Thread running...\n");
    printf("ID: %d\n", s->id);
    printf("Name: %s\n", s->name);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread_id;
    Student s;

    s.id = 1;
    strcpy(s.name, "Nguyen Van A");

    // Tạo thread, truyền struct vào
    if (pthread_create(&thread_id, NULL, printStudentInfo, (void*)&s) != 0) {
        perror("pthread_create failed");
        return 1;
    }

    // Chờ thread kết thúc
    pthread_join(thread_id, NULL);

    printf("Main thread done.\n");
    return 0;
}
