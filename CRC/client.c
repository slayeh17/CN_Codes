#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

#define SOCKET_PATH "./crc_socket"
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_un server;
    char buffer[BUFFER_SIZE];
    char dataWord[BUFFER_SIZE];
    char divisor[BUFFER_SIZE];

    client_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server, 0, sizeof(server));
    server.sun_family = AF_UNIX;
    strncpy(server.sun_path, SOCKET_PATH, sizeof(server.sun_path) - 1);

    if (connect(client_socket, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    printf("Enter data word: ");
    fgets(dataWord, BUFFER_SIZE, stdin);
    dataWord[strcspn(dataWord, "\n")] = '\0';

    printf("Enter divisor: ");
    fgets(divisor, BUFFER_SIZE, stdin);
    divisor[strcspn(divisor, "\n")] = '\0';

    strcat(buffer, dataWord);
    strcat(buffer, ",");
    strcat(buffer, divisor);

    if (send(client_socket, buffer, strlen(buffer), 0) == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    }

    if (recv(client_socket, buffer, BUFFER_SIZE, 0) == -1) {
        perror("recv");
        exit(EXIT_FAILURE);
    }

    printf("Received codeword from server: %s\n", buffer);

    close(client_socket);

    return 0;
}

