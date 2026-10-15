#include <func.h>

int main(void)
{
    printf("begin:");
    pid_t pid=fork();
    switch(pid){
    case -1:
        perror("fork");
    case 0:
        printf("I am baby\n");
        printf("pid=%d,ppid=%d\n",getpid(),getppid());
        break;
    default:
        printf("I am dad\n");
        printf("parent:pid=%d,childpid=%d\n",getpid(),pid);
        break;
    }
    printf("byebye\n");

    return 0;
}


