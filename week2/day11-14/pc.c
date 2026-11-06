#include <func.h>
#include "blockq.h"
void* start_routine(void* args);

typedef struct {
    int num;
    pthread_t *threads;
    BlockQ* q;
}ThreadPool;
ThreadPool *threadpool_create(int n)
{
    ThreadPool* pool = (ThreadPool *)malloc(sizeof(ThreadPool));
    pool->threads=(pthread_t*)malloc(n*sizeof(pthread_t));
    pool->num=n;
    pool->q=blockq_create();
    for(int i=0;i<n;i++)
    {
        pthread_create(pool->threads+i,NULL,start_routine,(void*)pool);
    }
    return pool;
}
void* start_routine(void* args)
{
    ThreadPool * pool=(ThreadPool*)args;
    pthread_t tid = pthread_self();
    for(;;)
    {
        E task_id=blockq_pop(pool->q);
        if(task_id==-1)
        {
            pthread_exit(NULL);
        }
        printf("0x%lx:execute task %d\n",tid,task_id);
        sleep(3);
        printf("0x%lx:task %d done\n",tid,task_id);
    }
    return NULL;
}
void threadpool_destory(ThreadPool* pool)
{
    blockq_destroy(pool->q);
    free(pool->threads);
    free(pool);
}

int main(void)
{
    ThreadPool* pool = threadpool_create(8);
    for(int i=0;i<100;i++)
    {
        blockq_push(pool->q,i+1);
    }
    sleep(5);
    for(int i=0;i<pool->num;i++)
    {
        blockq_push(pool->q,-1);
    }
    for(int i=0;i<pool->num;i++)
    {
        pthread_join(pool->threads[i],NULL);
    }
    threadpool_destory(pool);
    return 0;

}


