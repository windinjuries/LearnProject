---
title: cmake tutorial
date: 2024-2-25 12:00:00
tags: cmake
categories: 
- [Tutorial, Program Tool]
excerpt: "CMake是一个跨平台的安装（编译）工具，可以用简单的语句来描述所有平台的安装(编译过程)。他能够输出各种各样的makefile或者project文件"
comment: true
---
## cmake turtoial
### 环境配置
1. 运行环境：Linux
2. 编译工具：gcc/g++
3. 构建工具：cmake
### 构建最小项目
最基本的项目是将一个源代码文件生成可执行文件。对于这么简单的项目，只需要一个三行的 CMakeLists.txt 文件即可，第一步是创建一个 CMakeLists.txt文件，如下所示
```cmake
    # 设置cmake最低版本
    cmake_minimum_required(VERSION 3.15)
    # 设置工程名字
    project(Tutorial)
    # 添加可执行文件
    add_executable(Tutorial tutorial.cpp)
```
### 生成makefile文件和编译文件
先从命令行进入到 step1 目录，并创建一个构建目录 build，接下来，进入 build 目录并运行 CMake 来配置项目，并生成构建系统。
```shell
mkdir build
cd build
cmake ../CmakeList.text
```
### 优化CMakeLists.txt文件
1. 使用变量代替工程名
```cmake
add_executable(${PROJECT_NAME} tutorial.cpp)
```
2. 设置多个文件的变量
```cmake
set(SRC_LIST a.cpp b.cpp c.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})
```
set 命令指定 SRC_LIST 变量来表示多个源文件，用 ${var_name} 获取变量的值。
3. 添加版本号和设置头文件
```cmake
cmake_minimum_required(VERSION 3.15)
# set the project name and version
project(Tutorial VERSION 1.0)
configure_file(TutorialConfig.h.in TutorialConfig.h)
```
### 相关配置项
#### add_executable()

```cmake
add_executable(<name> [WIN32] [MACOSX_BUNDLE]
    [EXCLUDE_FROM_ALL]
    [source1] [source2 ...]
)
```
- 该命令用于定义一个可以构建成可执行程序的 Target。
- 第一个参数是 Target 的名字，这个参数必须提供。
- 第二个参数 WIN32 是可选参数，Windows 平台特定的参数，现在你不用管它的意思，不要使用它即可。后续我们需要使用到它的时候会说明其含义。
- 第三个参数 MACOSX_BUNDLE 同第二个参数，是 Apple 平台的特定参数，先忽略。
- 第四个参数 EXCLUDE_FROM_ALL 如果存在，那 CMake 默认构建的时候就不会构建这个 Target。
- 后续可选参数均为构建该可执行文件所需的源码，在这里可以省略，通过其他命令单独指定源码。但是对于入门，我们直接在这里指定源码文件即可。
#### add_library()
```cmake
add_library(<name> [STATIC | SHARED | MODULE]
    [EXCLUDE_FROM_ALL]
    [<source>...]
)
```
- 签名和 add_executable() 非常相似，该命令用于定义构建成库文件的 Target。
- 这里只讲差异，add_library() 命令支持可选的三个互斥参数：STATIC | SHARED | MODULE。
这三个参数要么都没有，要么只能有一个。对于简单的例子，我们可以指定构建库为 STATIC（静态库）、SHARED（动态库）、MODULE（类似于动态库，不过不会被其他库或者可执行程序链接，用于插件式框架的软件的插件构建）。
- 当然最佳实践是不要自己在 CMakeLists.txt 中指定这几个参数，而是把主动权交给构建者，通过 cmake -DBUILD_SHARED_LIBS=YES 的形式传值告诉其需要构建哪种库。
#### add_custom_target() 
```cmake
add_custom_target(Name [ALL] [command1 [args1...]]
    [COMMAND command2 [args2...] ...]
    [DEPENDS depend depend depend ... ]
    [BYPRODUCTS [files...]]
    [WORKING_DIRECTORY dir]
    [COMMENT comment]
    [JOB_POOL job_pool]
    [VERBATIM] [USES_TERMINAL]
    [COMMAND_EXPAND_LISTS]
    [SOURCES src1 [src2...]]
)
```
这个命令属于 CMake 高级用法中才会涉及的命令，这里只是为了说明 CMake 有哪些定义 Target 的方式才给它放在这里。从上面的命令签名你应该能看到，参数非常的多，也非常的复杂。所以这个命令的具体使用我们会在高级部分讲解。
### 基本语法
#### 基本变量
在学习这个命令的具体含义之前，我先讲几点 CMake 变量的约定：
- CMake 将所有的变量的值视为字符串
- 当给出变量的值不包含空格的时候，可以不使用引号，但建议都加上引号，不然一些奇怪的问题很难调试。
- CMake 使用空格或者分号作为字符串的分隔符
- CMake 中想要获取变量的值，和 shell 脚本一样，采用 ${var} 形式。
- 使用 CMake 变量前，不需要这个变量已经定义了，如果使用了未定义的变量，那么它的值是一个空字符串。
- 默认情况下使用未定义的变量不会有警告信息，但是可以通过 cmake 的 -warn-uninitialized 选项启用警告信息。
- 使用未定义的变量非常常见，如果出现问题也不一定是因为变量未定义导致的，所以 cmake 的 -warn-uninitialized 选项用处很有限。
- 变量的值可以包含换行，也可以包含引号，不过需要转义。
CMake 定义变量的命令如下：
```cmake
set(varName value... [PARENT_SCOPE])
```
- 第一个参数是必须的，代表要定义的变量的变量名。
- 第二个参数也是必须的，代表要定义的变量的值，根据上述 CMake 变量的约定，我们知道这里的 value 应该是一个字符串，而且不管有没有空格，都建议用引号引起来。
- 当然第二个参数可以是一个以空格或者分号隔开的字符串，这样定义的变量将是一个列表，对于列表我们后面会详细讲，这里大家可以忽略。在学习列表之前，大家只需要记住，value 只使用没有空格或者分号分割的单个字符串即可。
- 第三个参数是一个可选参数，意思是定义的这个变量的作用域属于父作用域，关于作用域我们后面也会详细讲解，本讲大家不要使用这个可选参数即可。
#### 环境变量
linux上可以使用 echo $PATH 这条命令看到环境变量 PATH 的值。
```cmake
set(ENV{PATH} "$ENV{PATH}:/opt/myDir")
message(STATUS "PATH=$ENV{PATH}")
```
#### 缓存变量
与普通变量不同，缓存变量的值可以缓存到 CMakeCache.txt 文件中，当再次运行 cmake 时，可以从中获取上一次的值，而不是重新去评估。所以缓存变量的作用域是全局的。
CMake 定义缓存变量的格式如下：
```cmake
set(varName value... CACHE type "docstring" [FORCE])
```
从上面的 CMake 定义缓存变量的命令中，我们可以看到，第一个参数依然是变量的名字，第二个参数是变量的值。缓存变量不同于普通变量是从第三个参数开始的，第三个参数是固定 CACHE 这个关键字，表示这条命令定义的是缓存变量。
第四个参数 type 是必选参数，而且其值必须是下列值之一。
- BOOL
BOOL 类型的变量值如果是 ON、TRUE、1 则被评估为真，如果是 OFF、FALSE、0 则被评估为假。
当然除了上面列出的值还有其他值，但是判断真假就没那么清晰了，所以建议定义 BOOL 类型的缓存变量的时候，其值就采用上述列出的值。虽然不区分大小写，但是我建议统一使用大小。
- FILEPATH
文件路径
- STRING
字符串
- INTERNAL
内部缓存变量不会对用户可见，一般是项目为了缓存某种内部信息时才使用，cmake 图形化界面工具也对其不可见。
内部缓存变量默认是 FORCE 的。
FORCE 关键字代表每次运行都强制更新缓存变量的值，如果没有该关键字，当再次运行 cmake 的时候，cmake 将使用 CMakeCache.txt 文件中缓存的值，而不是重新进行评估。
CMake 自身是将所有变量的值均视为字符串的，这里指定类型只是为了提高 cmake 图形界面工具的用户体验。

第五个参数是一个说明性的字符串，可以为空，只在图形化 cmake 界面会展示。

由于 BOOL 类型的变量使用频率非常高，CMake 为其单独提供了一条命令。

option(optVar helpString [initialValue])
第一个参数是变量的名字，第二个参数是提供帮助信息的字符串，可以为空字符串。 initialValue 是可选参数，代表缓存变量的值，如果没有提供，那该缓存变量的值默认为 OFF。

上述命令等价于：

set(optVar initialValue CACHE BOOL helpString)
不过上述两个命令定义缓存变量是有一点点区别的，option() 命令没有 FORCE 关键字。
#### 变量作用域


## 参考 
[Modern Cmake](https://modern-cmake-cn.github.io/Modern-CMake-zh_CN/chapters/intro/newcmake.html)