
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr,
                "Usage: %s directory\n", argv[0]);
        return 1;
    }

    // 打开目录流
    DIR *dir = opendir(argv[1]);

    if (dir == NULL)
    {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    int failed = 0;

    while (1)
    {
        errno = 0;

        // 读取下一个目录项
        entry = readdir(dir);

        if (entry == NULL)
        {
            if (errno != 0)
            {
                perror("readdir");
                failed = 1;
            }

            break;
        }

        // 跳过 . 和 ..
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        // 打印目录项名称
        printf("%s\n", entry->d_name);
    }

    // 关闭目录流
    if (closedir(dir) == -1)
    {
        perror("closedir");
        return 1;
    }

    return failed;
}

