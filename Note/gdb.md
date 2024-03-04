---
title: gdb tutorial
date: 2023-01-01 09:21:23
tags:
- gdb
categories: 
- [Tutorial, Program Tool]
excerpt: "GDB, the GNU Project debugger, allows you to see what is going on `inside' another program while it executes -- or what another program was doing at the moment it crashed."
comment: true
---
## command 
| **Command Name** | **Command Abbreviation** | **Command Description** |
|------------|--------------|------------|
| run | r | Run a program to be debugged |
| continue | c | Let the paused program continue to run |
| next | n | Run to the next line |
| step | s | Single-step execution, entering a function |
| until | u | Run to the specified line and stop |
| finish | fi | End the current called function and return to the previous called function |
| return | return | End the current called function and return to the previous called function with a specified value |
| print | p | Print the value of a variable or register |
| backtrace | bt | View the call stack of the current thread |
| frame | f | Switch to the specified stack of the current call thread |
| thread | thread | Switch to the specified thread |
| break | b | Add a breakpoint |
| tbreak | tb | Add a temporary breakpoint |
| delete | d | Delete a breakpoint |
| enable | enable | Enable a breakpoint |
| disable | disable | Disable a breakpoint |
| watch | watch | Monitor whether the value of a variable or memory address changes |
| list | l | Display source code |
| info | i | View breakpoint/thread information |
| ptype | ptype | View variable type |
| disassemble | dis | View assembly code |
| set args | set args | Set program startup command line arguments |
| show args | show args | View the set command line arguments |

### start
```fish
gdb main.out
gdb main.out -tui
```

## breakpoint
```fish
b main.c:20 if cnt = 1
```

