#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd;
    char *mapped_mem, * p;
    int flength = 1024;
    void * start_addr = 0;

    fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    flength = lseek(fd, 1, SEEK_END);
    write(fd, "\0", 1);
    lseek(fd, 0, SEEK_SET);
    mapped_mem = mmap(start_addr, flength, PROT_READ,MAP_PRIVATE,fd, 0);
    printf("%s\n", mapped_mem);
    close(fd);
    munmap(mapped_mem, flength);
    return 0;
}

 
