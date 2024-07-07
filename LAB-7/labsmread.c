#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>

int main() {
    const char* name = "myfile";
    int size = 4096;
    int sfd;
    void* ptr;

    sfd = shm_open(name, O_RDONLY, 0777);
    ftruncate(sfd, size);
    ptr = mmap(NULL, size, PROT_READ, MAP_SHARED, sfd, 0);

    while (1) {
        printf("Content read from shared memory: %s", (char*)ptr);
        sleep(3);  // Wait for 3 seconds
    }

    return 0;
}

