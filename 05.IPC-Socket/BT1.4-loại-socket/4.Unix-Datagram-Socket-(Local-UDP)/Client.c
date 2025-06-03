#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "/tmp/unix_dgram_socket"
#define CLIENT_SOCK_PATH "/tmp/unix_dgram_client_socket"

int main() {
    int sockfd;
    struct sockaddr_un serv_addr, cli_addr;
    socklen_t serv_len;
    char buffer[256];

    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd < 0) { perror("socket"); exit(1); }

    // Bind client socket to a unique path so server can reply
    unlink(CLIENT_SOCK_PATH);
    memset(&cli_addr, 0, sizeof(cli_addr));
    cli_addr.sun_family = AF_UNIX;
    strncpy(cli_addr.sun_path, CLIENT_SOCK_PATH, sizeof(cli_addr.sun_path)-1);
    if (bind(sockfd, (struct sockaddr *)&cli_addr, sizeof(cli_addr)) < 0) {
        perror("bind"); exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strncpy(serv_addr.sun_path, SOCK_PATH, sizeof(serv_addr.sun_path) - 1);

    serv_len = sizeof(serv_addr);

    char *msg = "Hello from Unix Datagram Client!";
    sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&serv_addr, serv_len);

    int n = recvfrom(sockfd, buffer, sizeof(buffer)-1, 0, NULL, NULL);
    if (n < 0) { perror("recvfrom"); exit(1); }
    buffer[n] = '\0';

    printf("Received: %s\n", buffer);

    close(sockfd);
    unlink(CLIENT_SOCK_PATH);
    return 0;
}
