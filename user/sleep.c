#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("input error\n");
        exit(0);
    }
        
    int tick_count = atoi(argv[1]);
    sleep(tick_count);
    exit(0);
}