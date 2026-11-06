#include <func.h>
typedef struct {
    int id;
    int balance;
    // 细粒度锁
    pthread_mutex_t mutex;
} Account;

Account acct1 = {1, 100, PTHREAD_MUTEX_INITIALIZER};
Account acct2 = {2, 900, PTHREAD_MUTEX_INITIALIZER};

int transfer(Account* acctA, Account* acctB, int money)
{
    if(acctA->id<acctB->id)
    {
    pthread_mutex_lock(&acctA->mutex);
    sleep(1);  // 切换
    pthread_mutex_lock(&acctB->mutex);
    }else{
    pthread_mutex_lock(&acctB->mutex);
    sleep(1);
    pthread_mutex_lock(&acctA->mutex);
    }

    
    if (acctA->balance < money) {
        pthread_mutex_unlock(&acctA->mutex);
        pthread_mutex_unlock(&acctB->mutex);
        return 0;
    }

    acctA->balance -= money;
    acctB->balance += money;

    pthread_mutex_unlock(&acctA->mutex);
    pthread_mutex_unlock(&acctB->mutex);

    return money;
}

void* start_routine1(void* arg)
{
    int money = (int)arg;

    int n = transfer(&acct1, &acct2, money);

    printf("acct1 transfer $%d to acct2\n", n);

    return NULL;
}

void* start_routine2(void* arg)
{
    int money = (int)arg;

    int n = transfer(&acct2, &acct1, money);

    printf("acct2 transfer $%d to acct1\n", n);

    return NULL;
}

int main(int argc, char* argv[])
{
    srand(time(NULL));

    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, start_routine1, (void*)100);
    pthread_create(&tid2, NULL, start_routine2, (void*)900);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}

