#include<func.h>
int main()
{
    int fd=open("hello.txt",O_WRONLY|O_TRUNC|O_CREAT,0666);
        if(fd==-1)
        {
            error(1,0,"open");
        }
        char buf[]="Hello world\n";
        ssize_t n=write(fd,buf,strlen(buf));
        if(n!=(ssize_t)strlen(buf))
        {
            perror("write");
        }

        close(fd);
        printf("count size=%zd\n",n);
        return 1;
}

