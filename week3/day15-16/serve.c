#include <func.h>
int main(void)
{
    char *ip = "192.168.106.130";
    char *port = "8080";
    // 1. 创建Socket
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        return 1;
    }
    // 2. 初始化地址结构体
    struct sockaddr_in sock = {0};
    sock.sin_family = AF_INET;
    // 3. 将IP地址转换成网络字节序
    if (inet_pton(AF_INET, ip, &sock.sin_addr) != 1) {
        printf("IP地址格式错误\n");
        close(fd);
        return 1;
    }
    // 4. 将端口转换成网络字节序
    sock.sin_port = htons(atoi(port));
    // 5. 绑定IP和端口
    if (bind(fd, (struct sockaddr*)&sock,
             sizeof(sock)) == -1) {
        perror("bind");
        close(fd);
        return 1;
    }
    printf("bind success!\n");
    close(fd);
    return 0;
}

