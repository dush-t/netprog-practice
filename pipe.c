#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void
main() {
    int pipe1[2];
    int pipe2[2];

    pipe(pipe1);
    pipe(pipe2);

    close(pipe2[1]);
    dup2(pipe1[1], pipe2[1]);

    pid_t child1 = fork();
    if (child1 == 0) {
        char buf[100];
        read(pipe1[0], buf, 100);
        printf("Child 1 (pid=%d) %s\n", getpid(), buf);
        return;
    }
    pid_t child2 = fork();
    if (child2 == 0) {
        char buf[100];
        read(pipe2[0], buf, 100);
        printf("Child 2 (pid=%d) %s\n", getpid(), buf);
        return;
    }

    write(pipe1[1], "hello", 6);
    return;
}