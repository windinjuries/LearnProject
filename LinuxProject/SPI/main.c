#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <linux/spi/spidev.h>

#define SPI_DEV_PATH "/dev/spidev0.0"

/*SPI 接收 、发送 缓冲区*/
unsigned char tx_buffer[128] = {0};
unsigned char rx_buffer[128] = {0};


int fd;                  					
static unsigned  mode = SPI_MODE_1;    
static uint8_t bits = 8;        			
static uint32_t speed = 1000;
static uint16_t delay = 0;          		

int transfer(int fd, uint8_t const *tx, uint8_t const *rx, size_t len)
{
    int ret = 0;

    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = len,
        .delay_usecs = delay,
        .speed_hz = speed,
        .bits_per_word = bits,
        .tx_nbits = 1,
        .rx_nbits = 1
    };

    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    
    if (ret < 1)
    {
        printf("can't send spi message\n");
        return -1;
    }
    printf("recv len = %d\n", tr.len);
    printf("recv len = %d\n", ret);
    printf("recv: %d %d\n", rx_buffer[0], rx_buffer[1]);
    return 0;
}
int spi_read_register(int fd, int command)
{
    int ret = 0;
    tx_buffer[0] = command;
    ret = write(fd, tx_buffer, 1);
    if (ret < 1)
    {
        printf("spi write error\n");
        return -1;
    }
    ret = read(fd, rx_buffer, 1);
    if (ret < 1)
    {
        printf("spi read register error\n");
        return -1;
    }
    printf("recv: %d \n", rx_buffer[0]);
    return 0;
}
int spi_write_enable(int fd)
{
    int ret = 0;
    tx_buffer[0] = 0x20;
    ret = transfer(fd, tx_buffer, rx_buffer, 1);
    if (ret != 0)
    {
        printf("spi write enable error\n");
        return -1;
    }
    return 0;
}

int spi_ecrase_section(int fd, int address)
{
    int ret = 0;
    tx_buffer[0] = 0x20;
    ret = transfer(fd, tx_buffer, rx_buffer, 3);
    if (ret != 0)
    {
        printf("spi write enable error\n");
        return -1;
    }
    return 0;
}
int spi_init(void)
{
    int ret = 0;
    //打开 SPI 设备
    fd = open(SPI_DEV_PATH, O_RDWR);
    if (fd < 0)
    {
        printf("can't open %s\n",SPI_DEV_PATH);
        return -1;
    }

    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    if (ret == -1)
    {
        printf("can't set spi mode\n");
        return -1;
    }

    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1)
    {
        printf("can't set bits per word\n");
        return -1;
    }

    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1)
    {
        printf("can't set max speed hz\n");
        return -1;
    }

    printf("spi mode: 0x%x\n", mode);
    printf("bits per word: %d\n", bits);
    printf("max speed: %d Hz (%d KHz)\n", speed, speed / 1000);
}
int spi_deinit(int fd)
{
    close(fd);
}

int main(int argc, char *argv[])
{
    spi_init();
    spi_read_register(fd, 0x05);
    spi_write_enable(fd);
    spi_read_register(fd, 0x05);
    spi_deinit(fd);
    return 0;
}