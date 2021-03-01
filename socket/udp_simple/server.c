#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int
main(int argc, char** argv) {
    int port = atoi(argv[1]);
    
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    
    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sock, (struct sockaddr*) &saddr, sizeof(saddr));

    while (1) {
        socklen_t len;
        len = sizeof(caddr);
        // Receive message
        printf("Waiting for message\n");
        char msg[256];
        int status = recvfrom(sock, msg, sizeof(msg), 0, (struct sockaddr*) &caddr, &len);
        printf("Received datagram from %s:%d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));
        printf("Data: %s\n", msg);

        // Send reply
        char reply[256] = "PONG";
        status = sendto(sock, reply, sizeof(reply), 0, (struct sockaddr*) &caddr, len);
    }

    return 0;
}