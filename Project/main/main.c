#include "log.h"
int main(int argc, char **argv)
{ 
    static int i = 0;
    while(1)
    {
        log_warn("i = %d", i);
        i++;
    }
    return 0;
}