#define LED_HTTP 6  
#define LED_PLAY 5  
#define LED_TIMER 8 

#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

#define GPIO_BASE   0x0300B000
#define PC_CFG0     2*0x0024+0x00
#define PC_CFG1     2*0x0024+0x04
#define PC_CFG2     2*0x0024+0x08
#define PC_CFG3     2*0x0024+0x0C

#define PC_DAT     2*0x0024+0x10
#define PC_DRV0    2*0x0024+0x14
#define PC_DRV1    2*0x0024+0x18


static volatile unsigned int * pc_cfg0_reg;
static volatile unsigned int * pc_cfg1_reg;
static volatile unsigned int * pc_data_reg;

void gpio_set_mode_out()
{
    //PCN            76543210
    *pc_cfg0_reg = 0x111fffff; 
    //PCN            fedcba98      
    *pc_cfg1_reg = 0xff11ff11; 
}
int gpio_led_onoff(int pin,int v)
{
    if(v==1){
        *pc_data_reg |= 0x01<<pin;
    }
    else{
        *pc_data_reg &= ~(0x01<<pin);
    }
}
int gpio_init()
{
    static int dev_fd;
    dev_fd = open("/dev/mem", O_RDWR );
    if (dev_fd < 0){
        printf("open(/dev/mem) failed.\n");
        return 0;
    }
    unsigned char *gpio_base;
    gpio_base = (unsigned char *)mmap(NULL, 4096,PROT_READ|PROT_WRITE, MAP_SHARED,dev_fd, GPIO_BASE); 
    if(!gpio_base)  
        printf("gpio_base mmap_fail!\n"); //是否映射成功

    pc_cfg0_reg = (volatile unsigned int * ) (gpio_base + PC_CFG0);
    // pc_cfg1_reg = (volatile unsigned int * ) (gpio_base + PC_CFG1);
    //pc_cfg2_reg = (volatile unsigned int * ) (gpio_base + PC_CFG2);
    //pc_cfg3_reg = (volatile unsigned int * ) (gpio_base + PC_CFG3);

    pc_data_reg = (volatile unsigned int * ) (gpio_base + PC_DAT);

    *pc_cfg0_reg = 0xffffffff;
    *pc_cfg1_reg = 0xffffffff;

    *pc_data_reg = 0x0000ffff;

    gpio_set_mode_out();
    while(1) {

    gpio_led_onoff(13,1);
    sleep(500);

    gpio_led_onoff(13,0);
    sleep(500);
    }

    close(dev_fd);
    return 0;
}

int main() 
{
    gpio_init();
}