
#include <func.h>

int main(void)
{
    int fd = open("dup.txt",
        O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    int fd2 = dup(fd);

    if (fd2 == -1) {
        perror("dup");
        close(fd);
        return 1;
    }

    printf("fd = %d, fd2 = %d\n", fd, fd2);

    write(fd, "ABC", 3);
    write(fd2, "DEF", 3);

    close(fd2);
    close(fd);

    return 0;
}


