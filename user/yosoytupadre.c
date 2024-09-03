#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    printf("Yo soy tu padre - dijo el proceso %d\n", getppid());

    int pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        printf("Child process (PID: %d, Parent PID: %d)\n", getpid(), getppid());

        int ancestor_gen0 = getancestor(0);
        int ancestor_gen1 = getancestor(1);
        int ancestor_gen2 = getancestor(2);
        int ancestor_invalid = getancestor(5);

        printf("getancestor(0) = %d\n", ancestor_gen0);
        printf("getancestor(1) = %d\n", ancestor_gen1);
        printf("getancestor(2) = %d\n", ancestor_gen2);
        printf("getancestor(5) = %d (expected -1)\n", ancestor_invalid);
    } else {
        wait(0);
    }

    exit(0);
}