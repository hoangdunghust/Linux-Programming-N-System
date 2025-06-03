#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "/tmp/unix_stream_socket"

int main() {
    int sockfd;
    struct sockaddr_un serv_addr;
    char buffer[256];

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd < 0) { perror("socket"); exit(1); }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strncpy(serv_addr.sun_path, SOCK_PATH, sizeof(serv_addr.sun_path) - 1);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect"); exit(1);
    }

    char *msg = "Hello from Unix Stream Client!";
    write(sockfd, msg, strlen(msg));

    memset(buffer, 0, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer) - 1);
    printf("Received: %s\n", buffer);

    close(sockfd);
    return 0;
}
