
#include <func.h>

int main(void)
{
    char *port="8080";
    char *ip="192.168.114.128";
    int socket_fd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serAddr;
    serAddr.sin_family=AF_INET;
    serAddr.sin_port=htons(atoi(port));
    serAddr.sin_addr.s_addr=inet_addr(ip);
    bind(socket_fd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    listen(socket_fd,10);
    int new_fd=accept(socket_fd,NULL,NULL);
    while(1)
    {
        char buf[60]={0};
        recv(new_fd,buf,sizeof(buf),0);
        printf("buf:%s\n",buf);
        memset(buf,0,sizeof(buf));
        read(STDIN_FILENO,buf,sizeof(buf));
        send(new_fd,buf,sizeof(buf),0);
    }

    close(new_fd);
    close(socket_fd);
    return 0;
}


