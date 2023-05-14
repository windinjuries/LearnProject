# Linux
## 命令
## grep
grep是指global search regular expression and print out the line：用于全面搜索的正则表达式 
语法格式
```shell
#option：选项 
#Pattern：搜索的正则表达式
#File：搜索文件
grep [OPTION...] PATTERNS [FILE...]
grep [OPTION...] -e PATTERNS ... [FILE...]
grep [OPTION...] -f PATTERN_FILE ... [FILE...]
# example
grep main main.c
```
### 管道命令 |
Linux管道命令是“ | ”，其作用是用来连接多条指令，前一条指令的输出流会作为后一条指令的操作对象，其命令格式为“指令1 | 指令2 | …”，该命令的后一条指令，必须能够接收标准输入流命令才能执行。
### 重定向 >
Linux 用于将指令的输出结果重定向到文件中
### nm
### xxd
### readelf
### objdump
### binutils
## modern unix指令
### exa
用于代替ls命令
### batcat
用于代替cat命令

