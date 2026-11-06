#include <func.h>
#include <arpa/inet.h>

int main(void)
{
    char ip[INET_ADDRSTRLEN];

    printf("请输入IP地址：");

    if (scanf("%15s", ip) != 1) {
        printf("输入错误\n");
        return 1;
    }

    // 定义IP地址结构体
    struct in_addr addr;

    // 点分十进制转换成32位网络字节序
    if (inet_aton(ip, &addr) == 0) {
        printf("IP地址格式错误\n");
        return 1;
    }

    printf("\n===== IP地址转换 =====\n");

    // 输出网络字节序对应的主机序整数
    printf("网络字节序转换后的主机序数值：0x%08x\n",
           (unsigned int)ntohl(addr.s_addr));

    // 网络字节序转换回点分十进制
    printf("转换回IP地址：%s\n", inet_ntoa(addr));

    // 再演示一次32位整数与网络字节序的转换
    uint32_t host_ip = ntohl(addr.s_addr);

    struct in_addr addr2;

    addr2.s_addr = htonl(host_ip);

    printf("通过htonl重新构造的IP：%s\n",
           inet_ntoa(addr2));

    return 0;
}
