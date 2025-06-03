#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "/tmp/unix_dgram_socket"

int main() {
    int sockfd;
    struct sockaddr_un serv_addr, cli_addr;
    socklen_t cli_len;
    char buffer[256];

    unlink(SOCK_PATH);

    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd < 0) { perror("socket"); exit(1); }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strncpy(serv_addr.sun_path, SOCK_PATH, sizeof(serv_addr.sun_path) - 1);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind"); exit(1);
    }

    printf("Unix Datagram Server waiting...\n");

    cli_len = sizeof(cli_addr);
    int n = recvfrom(sockfd, buffer, sizeof(buffer)-1, 0, (struct sockaddr *)&cli_addr, &cli_len);
    if (n < 0) { perror("recvfrom"); exit(1); }
    buffer[n] = '\0';

    printf("Received: %s\n", buffer);

    char *response = "Hello from Unix Datagram Server!";
    sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&cli_addr, cli_len);

    close(sockfd);
    unlink(SOCK_PATH);
    return 0;
}
