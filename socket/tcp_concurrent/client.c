#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int
main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int conn_stat = connect(sock, (struct sockaddr*) &server_address, sizeof(server_address));
    if (conn_stat == 1) {
        printf("Connection error!\n");
        return -1;
    }

    while (1) {
        char response[256];
        int status = read(sock, &response, sizeof(response));
        if (status == 0) {
            printf("Connection closed by server\n");
            break;
        }
        printf("Server sent: %s\n", response);
    }
    
    close(sock);
    return 0;
}