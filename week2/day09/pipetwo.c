
#include <func.h>

int main(void)
{
    int fd1[2];
    if(pipe(fd1)==-1)
    {
        perror("error");
    }

    int fd2[2];
    if(pipe(fd2)==-1)
    {
        perror("error");
    }
    char message[256];
    pid_t pid=fork();
    switch(pid)
    {
    case -1:
        perror("fork");
        
    case 0:
        close(fd1[1]);//write
        close(fd2[0]);//read
        read(fd1[0],message,256);
        printf("child:%s\n",message);
        write(fd2[1],"done!",6);
        exit(0);
    default:
        close(fd2[1]);//write
        close(fd1[0]);
        write(fd1[1],"homework down",14);    
        read(fd2[0],message,256);
        printf("Parent receive:%s\n",message);
        exit(0);
        
    }
    return 0;
}


