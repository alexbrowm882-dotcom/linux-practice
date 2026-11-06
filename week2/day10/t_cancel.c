#include <func.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void cleanup(void *arg)
{
    char *msg = (char *)arg;

    printf("执行清理函数：%s\n", msg);
}

void *worker(void *arg)
{
    (void)arg;

    // 注册清理函数
    pthread_cleanup_push(
        cleanup, "释放线程相关资源"
    );

    while (1) {
        printf("工作线程正在执行...\n");

        sleep(1);

        // 检查是否存在待处理的取消请求
        pthread_testcancel();
    }

    // 必须与 pthread_cleanup_push 配对
    pthread_cleanup_pop(0);

    return NULL;
}

int main(void)
{
    pthread_t tid;

    int err = pthread_create(
        &tid, NULL, worker, NULL
    );

    if (err != 0) {
        fprintf(stderr, "pthread_create: %s\n",
                strerror(err));
        return 1;
    }

    sleep(2);

    printf("主线程：请求取消工作线程\n");

    err = pthread_cancel(tid);

    if (err != 0) {
        fprintf(stderr, "pthread_cancel: %s\n",
                strerror(err));
        pthread_join(tid, NULL);
        return 1;
    }

    void *status = NULL;

    err = pthread_join(tid, &status);

    if (err != 0) {
        fprintf(stderr, "pthread_join: %s\n",
                strerror(err));
        return 1;
    }

    if (status == PTHREAD_CANCELED) {
        printf("工作线程已被取消\n");
    }

    return 0;
}
