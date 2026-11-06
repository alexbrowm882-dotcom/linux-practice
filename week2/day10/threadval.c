#include <func.h>
struct foo{
    int a;
    int b;
    int c;
};


void* worker(void *arg)
{
    (void)arg;
    printf("new pthread pid=%d,tid=%lu\n",(int)getpid(),(unsigned long)pthread_self());
    struct foo*x=(struct foo*)arg;
    printf("x=%d,y=%d,z=%d\n",x->a,x->b,x->c);
    return NULL;
}

int main(void)
{
    struct foo x={1,2,4};

    pthread_t tid;
    int err=pthread_create(&tid,NULL,worker,&x);
    if(err!=0)
        {
            perror("pthread_create");
        }

    printf("old pthread pid=%d,tid=%lu\n",(int)getpid(),(unsigned long)pthread_self());
    sleep(2);
    return 0;
}


