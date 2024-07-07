#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <time.h>

int main() {
    const char* name = "myfile";
    int size = 4096;
    int sfd;
    void* ptr;

    sfd = shm_open(name, O_CREAT | O_RDWR, 0777);
    ftruncate(sfd, size);
    ptr = mmap(NULL, size, PROT_WRITE, MAP_SHARED, sfd, 0);

    while (1) {
        time_t tm;
        time(&tm);
        sprintf(ptr, "%s", ctime(&tm));
        printf("Content written to shared memory: %s", (char*)ptr);
        sleep(3);  // Wait for 3 seconds
    }

    return 0;
}

