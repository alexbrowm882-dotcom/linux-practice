
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
    send(socket_fd,"hello",5,0);
    return 0;
}


