
#include <func.h>

int main(void)
{
    int fd=open("position.txt",O_RDWR|O_CREAT|O_TRUNC,0666);
    if(fd==-1)
    {
        perror("open");
    }
    write(fd,"abcdefghij",10);
    lseek(fd,3,SEEK_SET);
    write(fd,"XYZ",3);
    lseek(fd,0,SEEK_SET);
    char buf[20]={0};
    ssize_t n=read(fd,buf,sizeof(buf)-1);
    if(n==-1)
    {
        perror("read");
        close(fd);
        return 1;
    }
    buf[n]='\0';
    printf("neirong:%s\n",buf);
    close(fd);


    return 0;
}


