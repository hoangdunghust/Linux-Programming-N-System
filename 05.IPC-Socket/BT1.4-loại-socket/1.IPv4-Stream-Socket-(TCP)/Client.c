#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[256];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { perror("socket"); exit(1); }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect"); exit(1);
    }

    char *msg = "Hello from client!";
    write(sockfd, msg, strlen(msg));

    memset(buffer, 0, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer) - 1);
    printf("Received: %s\n", buffer);

    close(sockfd);
    return 0;
}
