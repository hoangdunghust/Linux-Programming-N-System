#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len;
    char buffer[256];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { perror("socket"); exit(1); }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(12345);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind"); exit(1);
    }

    listen(sockfd, 5);
    printf("Server listening on port 12345...\n");

    cli_len = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);
    if (newsockfd < 0) { perror("accept"); exit(1); }

    memset(buffer, 0, sizeof(buffer));
    read(newsockfd, buffer, sizeof(buffer) - 1);
    printf("Received: %s\n", buffer);

    char *response = "Hello from server!";
    write(newsockfd, response, strlen(response));

    close(newsockfd);
    close(sockfd);
    return 0;
}
