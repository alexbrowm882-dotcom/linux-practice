
#include <func.h>
#define MAX 256
int main(void)
{
    int fd1=open("pipe1",O_WRONLY);
    if(fd1==-1){
        perror("open1");
    }
    int fd2=open("pipe2",O_RDONLY);
    if(fd2==-1){
        perror("open2");
    }
    printf("Established\n");
    char recvline[MAX];
    char sendline[MAX];
    while(fgets(sendline,MAX,stdin)!=NULL)
    {
        write(fd1,sendline,strlen(sendline));
        read(fd2,recvline,MAX);
        printf("From S2:%s\n",recvline);
    }
    close(fd1);
    close(fd2);
    return 0;
}


