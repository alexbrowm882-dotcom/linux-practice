#include <func.h>
void* add1(void* arg)
{
    long long a=*(long long*)arg;
    int i;
    a>>=1;
    long long sum=0;
    for(i=1;i<=a;i++)
    {
        sum+=i;
    }
return (void*)sum;
}
void* add2(void* arg)
{
    long long a=*(long long*)arg;
    long long i;
    long long b=a;
    a=a>>1;
    long long sum=0;
    for(i=a+1;i<=b;i++)
    {
        sum+=i;
    }
return (void*)sum;
}
int main(void)
{
    long long n;
    printf("Please input n:\n");
    scanf("%lld",&n);
    int err1,err2;
    pthread_t tid1,tid2;
    err1=pthread_create(&tid1,NULL,add1,&n);
    if(err1!=0)
    {
        fprintf(stderr,"pthread_create=%s\n",strerror(err1));
        return 1;
    }
    err2=pthread_create(&tid2,NULL,add2,&n);
    if(err2!=0)
    {
        fprintf(stderr,"pthread_create=%s\n",strerror(err2));
        return 1;
    }
    void* sum1,*sum2;
    pthread_join(tid1,&sum1);
    pthread_join(tid2,&sum2);
    printf("sum1+sum2=%lld\n",(long long)sum1+(long long)sum2);
    return 0;
}


