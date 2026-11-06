
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

    fd_set rdset;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(socket_fd,&rdset);
        select(socket_fd+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset))
        {
        char buf[50]={0};
        read(STDIN_FILENO,buf,sizeof(buf));
        send(socket_fd,buf,sizeof(buf),0);
        }
        if(FD_ISSET(socket_fd,&rdset))
        {
        char buf[50]={0};
        int ret=recv(socket_fd,buf,sizeof(buf),0);
         if(ret==0){
            printf("connect brocken\n");
            break;
            }
        printf("buf:%s",buf);
        }
    }
    close(socket_fd);
    return 0;
}


