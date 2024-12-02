#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main() {
    char *filename = "testfile";

    // Create file with read/write permissions
    int fd = open(filename, O_CREATE | O_RDWR);
    write(fd, "Test", 4);
    close(fd);

    // Change to read-only and try writing
    chmod(filename, 1);
    fd = open(filename, O_WRONLY);
    if (fd >= 0) {
        printf("Error: Should not allow writing to read-only file\n");
    } else {
        printf("Success: Write blocked as expected\n");
    }

    // Change back to read/write and write again
    chmod(filename, 3);
    fd = open(filename, O_RDWR);
    write(fd, "Again", 5);
    close(fd);

    // Mark as immutable and try chmod
    chmod(filename, 5);
    if (chmod(filename, 3) < 0) {
        printf("Success: Immutable file cannot be changed\n");
    } else {
        printf("Error: Immutable file permissions were modified\n");
    }

    exit(0);
}