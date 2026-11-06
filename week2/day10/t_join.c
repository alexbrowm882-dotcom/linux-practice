#include <func.h>
void* worker(void*)
{
    sleep(3);
    return (void*)1234;
}

int main(void)
{
    pthread_t tid;
    int err=pthread_create(&tid,NULL,worker,NULL);
    if(err!=0)
        {
            perror("pthread_create");
        }
    int a;
    pthread_join(tid,(void**)&a);
    printf("main thread:a=%d\n",a);

    return 0;
}


