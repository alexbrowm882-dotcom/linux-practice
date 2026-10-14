
#include <func.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("用法: %s 文件名\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    struct stat st;

    if (fstat(fd, &st) == -1) {
        perror("fstat");
        close(fd);
        return 1;
    }

    printf("文件大小: %lld 字节\n",
           (long long)st.st_size);

    printf("inode: %llu\n",
           (unsigned long long)st.st_ino);

    printf("文件权限: %03o\n",
           (unsigned)(st.st_mode & 0777));

    printf("硬链接数: %llu\n",
           (unsigned long long)st.st_nlink);

    close(fd);
    return 0;
}


