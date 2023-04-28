#include "inc/main.h"
#include "inc/sub.h"
#include <pthread.h>
#include <bits/pthreadtypes.h>
#include <syslog.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
typedef struct 
{
    int num;
    pthread_mutex_t f_lock;
} st;
st st1;
void *thread1();
void *thread2();

int main(int argc, char *argv[], char *envp[])
{
    pthread_t pid1;
    pthread_t pid2;
    int error;
    error = pthread_mutex_init(&st1.f_lock, NULL);
    if (error < 0)
        return -1;
    error = pthread_create(&pid1, NULL, &thread1, NULL);
    if (error < 0)
        return -1;
    printf("%ld",pid1);
    error = pthread_create(&pid2, NULL, &thread1, NULL);
    if (error < 0)
        return -1;
    printf("%ld",pid2);
    while (1)
    {
        ;/* code */
    } 
}
void *thread1()
{
    pthread_t tid = gettid();
    while (1)
    {
        pthread_mutex_trylock(&(st1.f_lock));
        if (st1.num > 100)
            st1.num = 0;
        else
            st1.num++;
        printf("%d: i=%d\n", tid, st1.num);
        pthread_mutex_unlock(&(st1.f_lock));
        sleep(2); 
    }
}
