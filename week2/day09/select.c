

#include <func.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <errno.h>

int main(void)
{
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 0;
    }

    if (pid == 0) {
        // 子进程负责发送消息
        close(fd[0]);

        sleep(3);

        char msg[] = "Hello from child\n";
        write(fd[1], msg, strlen(msg));

        close(fd[1]);
        _exit(0);
    }

    // 父进程监听两个输入源
    close(fd[1]);

    char buf[128];
    int stdin_open = 1;

    printf("请输入文字，或等待子进程消息...\n");
    fflush(stdout);

    while (1) {
        fd_set readfds;
        FD_ZERO(&readfds);

        FD_SET(fd[0], &readfds);

        if (stdin_open) {
            FD_SET(STDIN_FILENO, &readfds);
        }

        int ret = select(fd[0] + 1,
                         &readfds, NULL, NULL, NULL);

        if (ret == -1) {
            if (errno == EINTR) continue;
            perror("select");
            break;
        }

        // 检查键盘是否有输入
        if (stdin_open &&
            FD_ISSET(STDIN_FILENO, &readfds)) {

            ssize_t n = read(STDIN_FILENO,
                             buf, sizeof(buf));

            if (n > 0) {
                printf("键盘：%.*s", (int)n, buf);
                fflush(stdout);
            } else {
                stdin_open = 0;
            }
        }

        // 检查管道是否有数据
        if (FD_ISSET(fd[0], &readfds)) {

            ssize_t n = read(fd[0],
                             buf, sizeof(buf));

            if (n > 0) {
                printf("管道：%.*s", (int)n, buf);
            } else {
                if (n < 0) perror("read");
                break;
            }
        }
    }

    close(fd[0]);
    waitpid(pid, NULL, 0);

    return 0;
}

