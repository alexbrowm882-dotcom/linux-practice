
#include <func.h>

int main(void)
{
    char *port="8080";
    char *ip="192.168.114.128";

    int socket_fd=socket(AF_INET,SOCK_STREAM,0);
     struct sockaddr_in cliAddr;
     cliAddr.sin_family=AF_INET;
     cliAddr.sin_port=htons(atoi(port));
     cliAddr.sin_addr.s_addr=inet_addr(ip);
    int res_connect=connect(socket_fd,(struct sockaddr*)&cliAddr,sizeof(cliAddr));
    if(res_connect==-1)
    {
        perror("connect");
        return -1;
    }
    while(1)
    {
        char buf[50]={0};
        read(STDIN_FILENO,buf,sizeof(buf));
        send(socket_fd,buf,sizeof(buf),0);
        memset(buf,0,sizeof(buf));
        recv(socket_fd,buf,sizeof(buf),0);
        printf("buf:%s",buf);
    }
    close(socket_fd);
    return 0;
}


