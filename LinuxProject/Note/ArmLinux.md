# ARM Linux
## Driver
### uboot
> bootloader初始化硬件和外设，构建内存空间，并加载内核到DDR中，相当于一个裸机程序

> [野火linux移植](https://doc.embedfire.com/lubancat/build_and_deploy/zh/latest/building_image/image_composition/image_composition.html)

### linux

### rootfs
> 根文件系统就是一个文件夹，包含许多文件，这些事Linux运行所必须的，但是无法放到内核中。
#### 构建工具
- busybox
- buildroot
- yocto

## Application
### GPIO
1. 寄存器方式
2. GPIO子系统(sysfs)  
3. libgpiod

### UART

### I2C

### SPI