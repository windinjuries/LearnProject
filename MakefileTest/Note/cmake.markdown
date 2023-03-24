## cmake turtoial
> CMake是一个跨平台的安装（编译）工具，可以用简单的语句来描述所有平台的安装(编译过程)。他能够输出各种各样的makefile或者project文件

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
该命令用于定义一个可以构建成可执行程序的 Target。
第一个参数是 Target 的名字，这个参数必须提供。
第二个参数 WIN32 是可选参数，Windows 平台特定的参数，现在你不用管它的意思，不要使用它即可。后续我们需要使用到它的时候会说明其含义。
第三个参数 MACOSX_BUNDLE 同第二个参数，是 Apple 平台的特定参数，先忽略。
第四个参数 EXCLUDE_FROM_ALL 如果存在，那 CMake 默认构建的时候就不会构建这个 Target。
后续可选参数均为构建该可执行文件所需的源码，在这里可以省略，通过其他命令单独指定源码。但是对于入门，我们直接在这里指定源码文件即可。
#### add_library()
#### add_custom_target() 

