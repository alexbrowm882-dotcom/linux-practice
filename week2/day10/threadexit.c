#include <func.h>
void* worker(void *arg)
{
    (void)arg;
    printf("new pthread pid=%d,tid=%lu\n",(int)getpid(),(unsigned long)pthread_self());
    return NULL;
}

int main(void)
{
    pthread_t tid;
    int err=pthread_create(&tid,NULL,worker,NULL);
    if(err!=0)
        {
            perror("pthread_create");
        }

    printf("old pthread pid=%d,tid=%lu\n",(int)getpid(),(unsigned long)pthread_self());
    sleep(2);
    return 0;
}


