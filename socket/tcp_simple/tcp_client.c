#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>


int
main() {
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int conn_stat = connect(sock, (struct sockaddr*) &server_address, sizeof(server_address));
    if (conn_stat == -1) {
        printf("Connection error!\n\n");
        return -1;
    }

    char server_response[256];
    recv(sock, &server_response, sizeof(server_response), 0);

    printf("Server sent data: %s \n", server_response);
    close(sock);

    return 0;
}