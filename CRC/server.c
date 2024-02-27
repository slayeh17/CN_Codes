#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

#define SOCKET_PATH "./crc_socket"
#define BUFFER_SIZE 1024
#define DATA_SIZE 10000

char* calculateCRC(char* dataWord, char* divisor) {
    int dataWordSize = strlen(dataWord);
    int divisorSize = strlen(divisor);

    char appendedData[DATA_SIZE];
    strcpy(appendedData, dataWord);
    for (int i = 0; i < divisorSize - 1; i++) {
        strcat(appendedData, "0");
    }

    for (int i = 0; i < dataWordSize; i++) {
        if (appendedData[i] == '1') {
            for (int j = 0; j < divisorSize; j++) {
                appendedData[i + j] = ((appendedData[i + j] == divisor[j]) ? '0' : '1');
            }
        }
    }

    char *codeword = malloc(dataWordSize);
    strncpy(codeword, appendedData + dataWordSize, dataWordSize);
    codeword[dataWordSize] = '\0';

    return codeword;
}

int main() {
    unlink(SOCKET_PATH);
    int server_socket, client_socket;
    socklen_t len;
    struct sockaddr_un server, client;
    char buffer[BUFFER_SIZE];
    char *codeword;

    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server.sun_family = AF_UNIX;
    strncpy(server.sun_path, SOCKET_PATH, sizeof(server.sun_path) - 1);

    if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on %s\n", SOCKET_PATH);

    while (1) {
        len = sizeof(client);
        client_socket = accept(server_socket, (struct sockaddr *)&client, &len);
        if (client_socket == -1) {
            perror("accept");
            continue;
        }

        printf("Client connected\n");

        if (recv(client_socket, buffer, BUFFER_SIZE, 0) == -1) {
            perror("recv");
            close(client_socket);
            continue;
        }

        char *dataWord = strtok(buffer, ",");
        char *divisor = strtok(NULL, ",");

        codeword = calculateCRC(dataWord, divisor);

        if (send(client_socket, codeword, strlen(codeword), 0) == -1) {
            perror("send");
        }

        printf("Codeword sent to client\n");

        close(client_socket);
    }

    close(server_socket);

    return 0;
}

