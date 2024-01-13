#include "log.h"
#include <stdio.h>
static char * TAG = "MAIN";
int main(int argc, char *argv[])
{ 
    __int32_t i = 12;
    if(-1 < i)
    {
        log_warn("y");
    }
    else
    {
        log_info("n");
    }
    return 0;
}