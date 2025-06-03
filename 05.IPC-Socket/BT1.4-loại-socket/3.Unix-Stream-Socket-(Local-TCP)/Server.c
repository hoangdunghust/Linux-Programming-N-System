#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "/tmp/unix_stream_socket"

int main() {
    int sockfd, newsockfd;
    struct sockaddr_un serv_addr, cli_addr;
    socklen_t cli_len;
    char buffer[256];

    unlink(SOCK_PATH);

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd < 0) { perror("socket"); exit(1); }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strncpy(serv_addr.sun_path, SOCK_PATH, sizeof(serv_addr.sun_path) - 1);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind"); exit(1);
    }

    listen(sockfd, 5);
    printf("Unix Stream Server listening...\n");

    cli_len = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);
    if (newsockfd < 0) { perror("accept"); exit(1); }

    memset(buffer, 0, sizeof(buffer));
    read(newsockfd, buffer, sizeof(buffer) - 1);
    printf("Received: %s\n", buffer);

    char *response = "Hello from Unix Stream Server!";
    write(newsockfd, response, strlen(response));

    close(newsockfd);
    close(sockfd);
    unlink(SOCK_PATH);
    return 0;
}
