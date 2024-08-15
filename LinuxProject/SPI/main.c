#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <linux/spi/spidev.h>

#include "elog.h"
#include "log.h"

// #define  __USE_POSIX
#define SPI_DEV_PATH "/dev/spidev0.0"

/*SPI 接收 、发送 缓冲区*/
unsigned char tx_buffer[128] = {0};
unsigned char rx_buffer[128] = {0};


int fd;                  					
static unsigned  mode = SPI_MODE_0;    
static uint8_t bits = 8;        			
static uint32_t speed = 1000000; // 1Mhz
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
        log_e("can't send spi message\n");
        return -1;
    }
    return 0;
}
int spi_read_id(int fd)
{
    int ret = 0;
    tx_buffer[0] = 0x9F;
    ret = transfer(fd, tx_buffer, rx_buffer, 1 + 3);
    if (ret != 0)
    {
        log_e("spi read flash id error\n");
        return -1;
    }
    log_d("SPI FLASH ID:  0x%X 0x%X 0x%X\n", rx_buffer[1], rx_buffer[2], rx_buffer[3]);
    return 0;

}
int spi_read_register(int fd, int command)
{
    int ret = 0;
    tx_buffer[0] = command;
    ret = transfer(fd, tx_buffer, rx_buffer, 1+1);
    if (ret != 0)
    {
        log_e("spi read register error\n");
        return -1;
    }
    log_d("status register-1: 0x%02X \n", rx_buffer[1]);
    return 0;
}
int spi_write_enable(int fd)
{
    int ret = 0;
    tx_buffer[0] = 0x06;
    ret = transfer(fd, tx_buffer, rx_buffer, 1);
    if (ret != 0)
    {
        log_e("spi write enable error\n");
        return -1;
    }
    return 0;
}

int spi_write(int fd, int address)
{
    int ret = 0;
    tx_buffer[0] = 0x02;
    tx_buffer[1] = (address & 0xFF0000) >> 16;
    tx_buffer[2] = (address & 0x00FF00) >> 8;
    tx_buffer[3] = address & 0x0000FF;
    tx_buffer[4] = 0x25;
    ret = transfer(fd, tx_buffer, rx_buffer, 5);
    if (ret != 0)
    {
        log_e("spi write enable error\n");
        return -1;
    }
    while(spi_read_register(fd, 0x05) || (rx_buffer[1] & 0x01) == 1)
    {
        log_d("wait finish\n");
        sleep(1);
    }
    log_d("spi write success\n");
    return 0;
}

int spi_read(int fd, int address)
{
    int ret = 0;
    tx_buffer[0] = 0x03;
    tx_buffer[1] = (address & 0xFF0000) >> 16;
    tx_buffer[2] = (address & 0x00FF00) >> 8;
    tx_buffer[3] = address & 0x0000FF;
    tx_buffer[4] = 0;
    ret = transfer(fd, tx_buffer, rx_buffer, 5);
    if (ret != 0)
    {
        log_e("spi write enable error\n");
        return -1;
    }
    log_d("read value: 0x%2X\n", rx_buffer[4]);

    return 0;
}
int spi_ecrase_chip(int fd)
{
    int ret = 0;
    tx_buffer[0] = 0x60;
    ret = transfer(fd, tx_buffer, rx_buffer, 3);
    if (ret != 0)
    {
        log_e("spi write enable error\n");
        return -1;
    }
    while(spi_read_register(fd, 0x05) || (rx_buffer[1] & 0x01) == 1)
    {
        log_e("wait finish\n");
        sleep(1);
    }
    log_d("spi ecrase chip success\n");
    return 0;
}
int spi_init(void)
{
    int ret = 0;
    fd = open(SPI_DEV_PATH, O_RDWR);
    if (fd < 0)
    {
        log_e("can't open %s\n",SPI_DEV_PATH);
        return -1;
    }

    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    if (ret == -1)
    {
        log_e("can't set spi mode\n");
        return -1;
    }

    ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
    if (ret == -1)
    {
        log_e("can't set spi mode\n");
        return -1;
    }

    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1)
    {
        log_e("can't set bits per word\n");
        return -1;
    }

    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret == -1)
    {
        log_e("can't set bits per word\n");
        return -1;
    }
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1)
    {
        log_e("can't set max speed hz\n");
        return -1;
    }

    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret == -1)
    {
        log_e("can't set max speed hz\n");
        return -1;
    }

    log_d("spi mode: 0x%x\n", mode);
    log_d("bits per word: %d\n", bits);
    log_d("max speed: %d Hz (%d KHz)\n", speed, speed / 1000);
    return 0;
}

int spi_deinit(int fd)
{
    close(fd);
    return 0;
}

int main(int argc, char *argv[])
{

    /* close printf buffer */
    setbuf(stdout, NULL);
    /* initialize EasyLogger */
    elog_init();
    /* set EasyLogger log format */
    elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);
    elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
    elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL & ~ELOG_FMT_FUNC);
#ifdef ELOG_COLOR_ENABLE
    elog_set_text_color_enabled(true);
#endif
    /* start EasyLogger */
    elog_start();

    log_d("hello");
    log_e("hello");
    spi_init();
    spi_read_id(fd);
    spi_read_register(fd, 0x05);
    spi_write_enable(fd);
    spi_ecrase_chip(fd);
    spi_write_enable(fd);
    spi_write(fd, 0x00FF10); 
    spi_read(fd, 0x00FF10); 
    spi_deinit(fd);
    return 0;
}