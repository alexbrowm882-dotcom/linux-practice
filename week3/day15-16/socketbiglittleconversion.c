#include <func.h>
#include <arpa/inet.h>
#include <stdint.h>

int main(void)
{
    // 1. 16位整数大小端转换
    uint16_t us = 0x1234;

    printf("===== 16位转换 =====\n");

    printf("转换前：%04x\n", (unsigned int)us);

    // 主机字节序转网络字节序
    uint16_t us1 = htons(us);

    printf("htons转换后：%04x\n", (unsigned int)us1);

    // 网络字节序转回主机字节序
    uint16_t us2 = ntohs(us1);

    printf("ntohs转换后：%04x\n", (unsigned int)us2);

    // 查看实际内存中的字节
    unsigned char *p16 = (unsigned char *)&us1;

    printf("网络字节序内存：%02x %02x\n",
           p16[0], p16[1]);


    // 2. 32位整数大小端转换
    uint32_t ul = 0x12345678;

    printf("\n===== 32位转换 =====\n");

    printf("转换前：%08x\n", (unsigned int)ul);

    // 主机字节序转网络字节序
    uint32_t ul1 = htonl(ul);

    printf("htonl转换后：%08x\n", (unsigned int)ul1);

    // 网络字节序转回主机字节序
    uint32_t ul2 = ntohl(ul1);

    printf("ntohl转换后：%08x\n", (unsigned int)ul2);

    unsigned char *p32 = (unsigned char *)&ul1;

    printf("网络字节序内存：%02x %02x %02x %02x\n",
           p32[0], p32[1], p32[2], p32[3]);

    return 0;
}

