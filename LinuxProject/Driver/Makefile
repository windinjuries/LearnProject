# compile by linux
# KERNEL_DIR=/home/fengzhishang/Desktop/orangepi-build/kernel/orange-pi-5.4-sun50iw9/
# ARCH=arm64
# CROSS_COMPILE=/home/fengzhishang/Desktop/orangepi-build/toolchains/gcc-arm-11.2-2022.02-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-
# export  ARCH  CROSS_COMPILE
obj-m := led_dev.o
KERNEL_DIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
build:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean