
#include <func.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("用法: %s src dst\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], argv[2]) == 0) {
        printf("源文件和目标文件不能相同\n");
        return 1;
    }

    int fd1 = open(argv[1], O_RDONLY);

    if (fd1 == -1) {
        perror("open src");
        return 1;
    }

    int fd2 = open(argv[2],
        O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (fd2 == -1) {
        perror("open dst");
        close(fd1);
        return 1;
    }

    char buf[1024];
    ssize_t n;

    while ((n = read(fd1, buf, sizeof(buf))) > 0) {
        ssize_t total = 0;

        while (total < n) {
            ssize_t m = write(fd2, buf + total,
                              n - total);

            if (m <= 0) {
                perror("write");
                close(fd1);
                close(fd2);
                return 1;
            }

            total += m;
        }
    }

    if (n == -1) {
        perror("read");
    }

    close(fd1);
    close(fd2);

    return n == -1 ? 1 : 0;
}

