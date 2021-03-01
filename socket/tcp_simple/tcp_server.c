#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int
main() {
    char server_message[256] = "Ooga booga unga bunga";

    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr*) &server_address, sizeof(server_address));

    listen(sock, 5);

    int client_sock;
    client_sock = accept(sock, NULL, NULL);

    send(client_sock, server_message, sizeof(server_message), 0);

    close(sock);

    return 0;
}