#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {
    char buf[512];
    char *exec_argv[MAXARG] = {0};
    int argv_idx = 0;

    for (int i = 1; i < argc; i++) {
        exec_argv[argv_idx++] = argv[i];
    }
    
    int buf_idx = 0;
    int len = 0;

    while (1) {
        int begin_idx = buf_idx;
        while (1) {
            len = read(0, &buf[buf_idx], 1);

            if (len == 0 || buf[buf_idx] == '\n') {
                buf[buf_idx] = 0;
                break;
            }

            buf_idx++;
        }

        if (len == 0)
            break;

        if (buf_idx == begin_idx)
            continue;

        buf[buf_idx++] = 0;    
        
        exec_argv[argv_idx++] = buf + begin_idx;
    }
    

    if (fork() == 0) {
        exec(argv[1], exec_argv);
        exit(0);
    }
    else {
        wait(0);
    }
    exit(0);
} 