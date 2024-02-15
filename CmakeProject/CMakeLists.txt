cmake_minimum_required(VERSION 3.5)

project(HelloWorld)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-Wl,-Map,target.map -DLOG_USE_COLOR")

include_directories(log/src)
 
set(DIR_SRCS ./main/main.c)
 
add_subdirectory(log)
 
add_executable(HelloWorld ${DIR_SRCS})
 
target_link_libraries(HelloWorld log)