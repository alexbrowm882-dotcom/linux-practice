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
        printf("childpid=%d\n",getpid());
        sleep(2);
        printf("exit child\n");
        exit(42);
        break;
    default:
        int status;
        printf("wait child\n");
        pid_t ret=waitpid(pid,&status,0);
        if(ret==-1){
            perror("waitpid");
            return 1;
        }
        if(WIFEXITED(status))
        {
        printf("exit code=%d\n",WEXITSTATUS(status));
        }

        break;
    }
    printf("byebye\n");

    return 0;
}


