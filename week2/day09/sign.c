
#include <func.h>
void hander(int signo)
{
    switch(signo)
    {
    case SIGINT:
        printf("caught SIGINT\n");
        break;
    case SIGTSTP:
        printf("caught SIGTSTP\n");
        break;
    default:
        printf("UNKNOWON\n");
    }

}
int main(void)
{
    sighandler_t oldhander=signal(SIGINT,hander);
    if(oldhander==SIG_ERR){
        perror("SIGINT");
    }
    oldhander=signal(SIGTSTP,hander);
    if(oldhander==SIG_ERR){
        perror("SIGTSTP");
    }
    for(;;){}
    return 0;
}


