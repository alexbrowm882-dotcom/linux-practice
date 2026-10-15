
#include <func.h>
#include <sys/wait.h>

int main(void)
{
    int fd = open("shared.txt",
        O_RDWR | O_CREAT | O_TRUNC, 0666);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        close(fd);
        return 1;
    }

    if (pid == 0) {
        // 子进程
        if (write(fd, "HELLO", 5) != 5) {
            perror("write");
            _exit(1);
        }

        close(fd);
        _exit(0);
    }
    else {
        // 等待子进程结束
        waitpid(pid, NULL, 0);

        off_t pos = lseek(fd, 0, SEEK_CUR);

        printf("父进程当前偏移量: %ld\n",
               (long)pos);

        write(fd, "WORLD", 5);

        close(fd);
    }

    return 0;
}


