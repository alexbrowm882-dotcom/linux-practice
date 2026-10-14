
#include <func.h>

int main(void)
{
    int fd = open("cut.txt",
        O_RDWR | O_CREAT | O_TRUNC, 0666);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    write(fd, "ABCDEFGHIJ", 10);

    // 将文件截断为5字节
    if (ftruncate(fd, 5) == -1) {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}

