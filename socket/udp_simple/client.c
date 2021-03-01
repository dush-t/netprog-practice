#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int
main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9001);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);

    char msg[256] = "PING";
    int status = sendto(sock, msg, sizeof(msg), 0, (struct sockaddr*) &saddr, sizeof(saddr));
    printf("Sent message %s\n", msg);
    
    char reply[256];
    socklen_t len = sizeof(caddr);
    status = recvfrom(sock, reply, sizeof(reply), 0, (struct sockaddr*) &caddr, &len);
    printf("Got reply from %s:%d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));
    printf("Data: %s\n", reply);

    return 0;
}