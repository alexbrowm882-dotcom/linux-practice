#include<func.h>
#include <fcntl.h>
int main(int argc,char *argv[])
    {
        if(argc!=2)
        {
            error(1,0,"Usage:%s",argv[0]);
        }
        int fd=open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0666);
        if(fd==-1)
        {
            error(1,errno,"open %s",argv[1]);
        }
        printf("fd=%d\n",fd);
        return 0;

    }

