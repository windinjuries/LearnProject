# ARM Linux

## Driver

### uboot
bootloader初始化硬件和外设，构建内存空间，并加载内核到DDR中，相当于一个裸机程序

### linux
Linux是一种开源电脑操作系统内核。它是一个用C语言写成，符合POSIX标准的类Unix操作系统。

### rootfs
根文件系统就是一个文件夹，包含许多文件，这些是Linux运行所必须的，但是无法放到内核中。

### 构建工具
- buildroot
- yocto

### reference
[embedfire linux](https://doc.embedfire.com/lubancat/build_and_deploy/zh/latest/building_image/image_composition/image_composition.html)  
[embedfire driver](https://doc.embedfire.com/linux/imx6/driver/zh/latest/README.html)

## Application

### GPIO
-  寄存器方式
-  GPIO子系统(sysfs)  

