#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

char *led_on = "1\n";
char *led_off= "0\n";

int main(void)
{
    int fd_0 = open("/dev/led_dev0", O_RDWR);
    if (fd_0 > 0)
        printf("led_dev0 open success\n");
    else
        printf("led_dev0 open fail\n");

    int fd_1 = open("/dev/led_dev1", O_RDWR);
    if (fd_1 > 0)
        printf("led_dev1 open success\n");
    else
        printf("led_dev1 open fail\n");
    for (;;)
    {
        write(fd_0, led_on, strlen(led_on));
        write(fd_1, led_on, strlen(led_on));
        sleep(2);
        write(fd_0, led_off, strlen(led_off));
        write(fd_1, led_off, strlen(led_off));
        sleep(2);
    }
    return 0;
}