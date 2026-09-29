
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr,
                "Usage: %s dirname mode\n", argv[0]);
        return 1;
    }

    // 使用八进制解析权限
    char *end;
    errno = 0;

    long mode = strtol(argv[2], &end, 8);

    // 验证权限是否合法
    if (errno != 0 ||
        end == argv[2] ||
        *end != '\0' ||
        mode < 0 ||
        mode > 0777)
    {
        fprintf(stderr, "Invalid mode\n");
        return 1;
    }

    // 创建目录
    if (mkdir(argv[1], (mode_t)mode) == -1)
    {
        perror("mkdir");
        return 1;
    }

    printf("Directory created: %s\n", argv[1]);

    return 0;
}

