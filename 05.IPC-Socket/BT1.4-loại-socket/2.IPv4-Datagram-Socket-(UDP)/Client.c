#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;
    socklen_t serv_len;
    char buffer[256];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) { perror("socket"); exit(1); }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    serv_len = sizeof(serv_addr);

    char *msg = "Hello from UDP client!";
    sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&serv_addr, serv_len);

    int n = recvfrom(sockfd, buffer, sizeof(buffer)-1, 0, NULL, NULL);
    if (n < 0) { perror("recvfrom"); exit(1); }
    buffer[n] = '\0';
    printf("Received: %s\n", buffer);

    close(sockfd);
    return 0;
}
