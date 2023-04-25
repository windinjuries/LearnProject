#include "inc/main.h"
#include "inc/sub.h"
#include <pthread.h>
void *thread1();
int main(int argc, char *argv[], char *envp[])
{
    pthread_t pid;
    int error = pthread_create(&pid, NULL, &thread1, NULL);
    if (error < 0)
        return -1;
    while(1);
}
void *thread1()
{
    int i = 0;
    while (1)
    {
        if (i > 100)
            i = 0;
        else
            i++;
        sleep(100);
        printf("i=%d\n", i);
    }
}