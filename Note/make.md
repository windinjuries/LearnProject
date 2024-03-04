---
title: makefile tutorial
date: 2023-06-01 09:21:23
tags:
- make
categories: 
- [Tutorial, Program Tool]
excerpt: "Make 可自动决定一个大程序中哪些文件需要重新编译，并发布重新编译它们的命令。本版本GNU Make使用手册由Richard M. Stallman and Roland McGrath编著。"
comment: true
---
### 参考文献
1. [GNU官网](https://gcc.gnu.org/)
2. [GNU Make使用手册](https://blog.51cto.com/u_14592069/5712502)
3. [GNU编译工具链](https://zhuanlan.zhihu.com/p/351841622)
### 编译工具
![编译流程](https://pic3.zhimg.com/80/v2-f92135d4a22a339cbe8984a2dc529ae6_720w.webp)
#### gcc
```
grep [OPTION [file/dir/NULL]] file
```
选项：
1. -E 只激活预处理,这个不生成文件, 你需要把它重定向到一个输出.i文件里面。
2. -S 只激活预处理和编译，就是指把文件编译成为汇编代码，生成.s文件
3. -c 只激活预处理,编译,和汇编,也就是他只把程序做成.o文件
4. -o 制定目标名称
5. -g 只是编译器，在编译的时候，产生调试信息。 
6. -O0 、-O1 、-O2 、-O3 编译器的优化选项的 4 个级别，-O0 表示没有优化, -O1 为默认值，-O3 优化级别最高。
#### g++
### 基本语法
#### 变量
在makefile中有两种变量：
- 简单变量(即时变量)：
A := xxx // A的值即刻确定，在定义时即确定
对于即时变量使用“:=”表示，它的值在定义的时候已被确定。
- 延时变量
B = xxx // B的值被使用到时才确定
对于延时变量使用“=”表示。它只有在使用到的时候才确定，在定义/等于时并没有确定下来。
想使用变量的时候使用“$”来引用，如果不想看到命令时，可以在命令的前面加上”@”符号，则不会显示命令本身。

当我们执行make命令的时候，make这个指令本身，会把整个Makefile读进去，进行全部分析，然后解析里面的变量。常用的变量的定义如下：
```Makefile
:= #即时变量
=  #延时变量
?= #延时变量, 如果是第一次定义才起效, 如果在前面该变量已定义则忽略这句
+= #附加, 它是即时变量还是延时变量取决于前面的定义
?=: #如果这个变量在前面已经被定义，这句话就不会起效果。
```
### 多文件编译示例
#### 目录结构
```
project
│   README.md
│   main.c
|    Makefile
|  Makefile.build
│
└───src
│   │   sub.c
│   │   Makefile
| 
└───inc
    │   main.h
    │   sub.h
```
### ./Makefile代码
```makefile
CROSS_COMPILE = # 交叉编译工具头,如：arm-linux-gnueabihf-
AS      = $(CROSS_COMPILE)as # 把汇编文件生成目标文件
LD      = $(CROSS_COMPILE)ld # 链接器，为前面生成的目标代码分配地址空间，将多个目标文件链接成一个库或者一个可执行文件
CC      = $(CROSS_COMPILE)gcc # 编译器，对 C 源文件进行编译处理，生成汇编文件
CPP    = $(CC) -E
AR      = $(CROSS_COMPILE)ar # 打包器，用于库操作，可以通过该工具从一个库中删除或则增加目标代码模块
NM     = $(CROSS_COMPILE)nm # 查看静态库文件中的符号表

STRIP       = $(CROSS_COMPILE)strip # 以最终生成的可执行文件或者库文件作为输入，然后消除掉其中的源码
OBJCOPY  = $(CROSS_COMPILE)objcopy # 复制一个目标文件的内容到另一个文件中，可用于不同源文件之间的格式转换
OBJDUMP = $(CROSS_COMPILE)objdump # 查看静态库或则动态库的签名方法

# 共享到sub-Makefile
export AS LD CC CPP AR NM
export STRIP OBJCOPY OBJDUMP

# -Wall ： 允许发出 GCC 提供的所有有用的报警信息
# -O2 : “-On”优化等级
# -g : 在可执行程序中包含标准调试信息
# -I : 指定头文件路径（可多个）
CFLAGS := -Wall -O2 -g 
CFLAGS += -I $(shell pwd)/inc

# LDFLAGS是告诉链接器从哪里寻找库文件，这在本Makefile是链接最后应用程序时的链接选项。
LDFLAGS := 

# 共享到sub-Makefile
export CFLAGS LDFLAGS

# 顶层路径
TOPDIR := $(shell pwd)
export TOPDIR

# 最终目标
TARGET := test

# 本次整个编译需要源 文件 和 目录
# 这里的“obj-y”是自己定义的一个格式，和“STRIP”这些一样，*但是 一般内核会搜集 ”obj-”的变量*
obj-y += main.o # 需要把当前目录下的 main.c 编进程序里
obj-y += src/ # 需要进入 subdir 这个子目录去寻找文件来编进程序里，具体是哪些文件，由 subdir 目录下的 Makefile 决定。
#obj-y += $(patsubst %.c,%.o,$(shell ls *.c))

# 第一个目标
all : start_recursive_build $(TARGET) 
	@echo $(TARGET) has been built !
	
# 处理第一个依赖，**转到 Makefile.build 执行**
# -C 选择执行的目录
# -f 选择执行的文件
start_recursive_build:
	make -C ./ -f $(TOPDIR)/Makefile.build
	
# 处理最终目标，把前期处理得出的 built-in.o 用上
$(TARGET) : built-in.o
	$(CC) -o $(TARGET) built-in.o $(LDFLAGS)
	
# 清理*.o
clean:
	rm -f $(shell find -name "*.o")
	rm -f $(TARGET)
	
# 彻底清理*.o *.d
distclean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
	rm -f $(TARGET)
```
Makefile.build
```Makefile
# 伪目标
PHONY := __build
__build:

# 清空需要的变量
obj-y :=
subdir-y :=
EXTRA_CFLAGS :=

# 包含同级目录Makefile
# 相对路径为执行 Makefile.build 的路径
include Makefile

# 获取当前 Makefile 需要编译的子目录的目录名
# filter过滤包含%/的文件，patsubst替换%/为%
__subdir-y	:= $(patsubst %/,%,$(filter %/, $(obj-y)))
subdir-y	+= $(__subdir-y)

# 把子目录的目标定为以下注释
# built-in.o d/built-in.o
subdir_objs := $(foreach f,$(subdir-y),$(f)/built-in.o)

# 获取当前目录需要编进程序的文件名作为，并写为目标
# a.o b.o
cur_objs := $(filter-out %/, $(obj-y))
# 使修改头文件 .h 后，重新make后可以重新编译（重要）
dep_files := $(foreach f,$(cur_objs),.$(f).d)
# 列出存在的文件
dep_files := $(wildcard $(dep_files))

ifneq ($(dep_files),)
  include $(dep_files)
endif


PHONY += $(subdir-y)

# 第一个目标
__build : $(subdir-y) built-in.o
# 优先编译 子目录的内容
#-C 选择子文件夹subdir-y执行
$(subdir-y):
	@echo "obj-y:"$(obj-y)
	@echo "subdir-y:"$(subdir-y)
	make -C $@ -f $(TOPDIR)/Makefile.build

# 将文件和子目录文件链接成目标
built-in.o : $(cur_objs) $(subdir_objs)
	@echo "built-cur_objs:" $(cur_objs)
	@echo "built-sub_dir:" $(subdir_objs)
	$(LD) -r -o $@ $^

dep_file = .$@.d
# 生成 cur_objs 目标
%.o : %.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(CFLAGS_$@) -Wp,-MD,$(dep_file) -c -o $@ $<
	
.PHONY : $(PHONY)
	echo "test"
```
./src/Makefile
```makefile
EXTRA_CFLAGS  := 
CFLAGS_test.o := 

obj-y += sub.o
#obj-y += subdir/
```