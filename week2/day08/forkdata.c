#include <func.h>
int a_value=100;
int main(void)
{
    int s_value=200;
    int *f_value=(int*)malloc(sizeof(int));
    *f_value=300;
    printf("begin:");
    pid_t pid=fork();
    switch(pid){
    case -1:
        perror("fork");
    case 0:
        a_value+=1000;
        s_value+=1000;
        *f_value+=1000;
        printf("child:a_value=%d,s_value=%d,f_value=%d\n",a_value,s_value,*f_value);
        break;
    default:
        sleep(2);
        printf("dad:a_value=%d,s_value=%d,f_value=%d\n",a_value,s_value,*f_value);
        break;
    }
    printf("byebye\n");

    return 0;
}


