#define _GNU_SOURCE
#include "inc/main.h"
#include "inc/sub.h"
#include <pthread.h>
#include <bits/pthreadtypes.h>
#include <syslog.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
typedef int inta;
typedef int intb;
typedef int intc;
int main(int argc, char *argv[])
{
    int a = 10;
    int *p = &a;
    *p = 10;
    while(1)
    {
        printf("%d\n", *p);
        printf("%x\n", p);
    }
}
