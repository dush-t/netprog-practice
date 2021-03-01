#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int root_pid;
pid_t next_pid;

void
main(int argc, char** argv) {
    int N = atoi(argv[1]);
    root_pid = getpid();

    for (int i = 0; i < N-1; i++) {
        pid_t next = fork();
        if (next > 0) {
            next_pid = next;
            break;
        }
        if (i == N-2) {
            next_pid = root_pid;
        }
    }

    printf("Process %d, next process %d\n", getpid(), next_pid);
}