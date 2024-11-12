#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "user.h"

int main() {
    char *addr = sbrk(0);  // Get the current heap address
    sbrk(4096);  // Reserve one page

    // Try to protect the new page
    if (mprotect(addr, 1) == -1) {
        printf("mprotect failed\n");
    } else {
        printf("mprotect succeeded, page should be read-only now.\n");
    }

    // Attempt to write to the protected page
    char *ptr = addr;
    printf("Attempting to write to protected page...\n");
    *ptr = 'A';  // This should fail if protection works
    printf("Value at address (expected failure): %c\n", *ptr);

    // Now remove the protection and try writing again
    if (munprotect(addr, 1) == -1) {
        printf("munprotect failed\n");
    } else {
        printf("munprotect succeeded, page should be writable now.\n");
    }

    // Attempt to write again after removing protection
    printf("Attempting to write to unprotected page...\n");
    *ptr = 'B';
    printf("Value at address (expected success): %c\n", *ptr);

    printf("Heap address before sbrk: %p\n", addr);
    addr = sbrk(4096);  // Expand by one page
    printf("Heap address after sbrk: %p\n", addr);

    return 0;
}
