
#include <func.h>

int main(void)
{
    int fd = open("sync.txt",
        O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buf[] = "Hello Linux!\n";

    if (write(fd, buf, strlen(buf)) !=
        (ssize_t)strlen(buf)) {
        perror("write");
        close(fd);
        return 1;
    }

    if (fsync(fd) == -1) {
        perror("fsync");
        close(fd);
        return 1;
    }

    printf("文件同步成功\n");

    close(fd);
    return 0;
}

