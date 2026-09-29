
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr,
                "Usage: %s dirname\n", argv[0]);
        return 1;
    }



    // 删除空目录
    // 删除空目录
    if (rmdir(argv[1]) == -1)
    {
        perror("rmdir");
        return 1;
    }

    printf("Directory removed: %s\n", argv[1]);

    return 0;
}

