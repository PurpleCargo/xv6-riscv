#include "kernel/types.h"
#include "user/user.h"

int main(void) {
    int i;    

    for (i = 0; i < 20; i++) {
        int pid = fork();
        if (pid == 0) {
            int mypid = getpid();

            printf("Ejecutando proceso %d (pid: %d)\n", i, mypid);           

            sleep(10);
            exit(0);
        }
        //sleep(1);
    }

    for(i = 0; i < 20; i++) {
        wait(0);
    }

    exit(0);
}