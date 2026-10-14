
#include<func.h>

int main(void)
{
    int fd = open("hello.txt", O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buf[1024] = {0};

    ssize_t n = read(fd, buf, sizeof(buf) - 1);

    if (n == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    buf[n] = '\0';

    printf("读取内容：%s", buf);

    close(fd);
    return 0;
}


