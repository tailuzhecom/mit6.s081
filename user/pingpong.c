#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int p1[2];
    int p2[2];
    pipe(p1);
    pipe(p2);
    if (fork() == 0) {
        char buf[8];
        read(p1[0], buf, sizeof(8));
        printf("%d: received ping\n", getpid());
        write(p2[1], "a", 1);
    }
    else {
        char buf[8];
        write(p1[1], "a", 1);
        read(p2[0], buf, sizeof(buf));
        printf("%d: received pong\n", getpid());
    }
    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]);
    exit(0);
}