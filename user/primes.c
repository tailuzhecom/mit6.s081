#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void child_process(int p[]) {
    int child_p[2];
    close(p[1]);

    int prime;
    int len = read(p[0], &prime, sizeof(int));
    if (len == 0) {
        close(p[0]);
        exit(0);
    }
  
    printf("prime %d\n", prime);
    pipe(child_p);
    int num;
    if (fork() == 0) {
        close(p[0]);
        child_process(child_p);
    }
    else {
        close(child_p[0]);
        while (1) {
            len = read(p[0], &num, sizeof(int));
            if (len == 0) {
                close(p[0]);
                close(child_p[1]);
                wait(0);
                exit(0);
            }
            else {
                if (num % prime != 0) {
                    write(child_p[1], &num, sizeof(int));
                }
            }
        }
        
    }

}

int main(int argc, char *argv[]) {
    int p0[2];
    pipe(p0);
    if (fork() == 0) {
        child_process(p0);
    }
    else {
        close(p0[0]);
        for (int i = 2; i <= 35; i++) {
            write(p0[1], &i, sizeof(int));
        }
        close(p0[1]);
        wait(0);
    }
    exit(0);
}