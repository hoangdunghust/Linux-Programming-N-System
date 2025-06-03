#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len;
    char buffer[256];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) { perror("socket"); exit(1); }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(12345);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind"); exit(1);
    }

    printf("UDP Server waiting...\n");
    cli_len = sizeof(cli_addr);

    int n = recvfrom(sockfd, buffer, sizeof(buffer)-1, 0, (struct sockaddr *)&cli_addr, &cli_len);
    if (n < 0) { perror("recvfrom"); exit(1); }
    buffer[n] = '\0';
    printf("Received: %s\n", buffer);

    char *response = "Hello from UDP server!";
    sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&cli_addr, cli_len);

    close(sockfd);
    return 0;
}
