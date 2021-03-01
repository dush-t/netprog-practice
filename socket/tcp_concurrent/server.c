#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

void sigchild_handler (int signum) {
    printf("Child process killed\n");
    pid_t pid;
    while ((pid = waitpid(-1, NULL, WNOHANG) > 0));
}

int
main(int argc, char** argv) {
    signal(SIGCHLD, sigchild_handler);

    int port = atoi(argv[1]);
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr*) &server_address, sizeof(server_address));

    listen(sock, 5);

    while (1) {
        struct sockaddr_in caddr;
        int address_len = sizeof(caddr);
        int csock = accept(sock, (struct sockaddr*) &caddr, &address_len);
        if (csock < 0) {
            printf("Error accepting client connection\n");
            continue;
        }
        printf("Accepted connection from client\n");
        printf("IP=%s | Port=%d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));

        if (fork() == 0) {
            char message[256] = "Sequence number = ";
            for (int i = 0; i < 15; i++) {
                char message[256];
                sprintf(message, "Sequence number = %d", i);
                send(csock, message, sizeof(message), 0);
                sleep(1);
            }
            printf("Closing connection\n");
            return 0;
        }

        close(csock);
    }
}