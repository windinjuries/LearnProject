include_directories(./log/src/)
 
set(DIR_SRCS ${PROJECT_SOURCE_DIR}/log/src/log.c)
MESSAGE(STATUS "可执行程序的目录（绝对路径）：" ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "当前目录（绝对路径）：" ${PROJECT_SOURCE_DIR})
add_library(log SHARED ${DIR_SRCS})