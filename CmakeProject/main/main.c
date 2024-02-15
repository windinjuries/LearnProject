#include "log.h"
#include <stdio.h>
#include <stdint.h>
int main(int argc, char *argv[])
{ 
    int32_t i = 12;
    if(-1 < i)
    {
        log_warn("y %d", 1); 
    }
    else
    {
        log_info("n");
    }
    return 0;
}