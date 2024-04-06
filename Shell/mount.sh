#!/bin/bash
local_dir=/home/orangepi/mnt
remote_dir=/home/fengzhishang/Desktop/LearnProject
remote_ip=192.168.31.148
mount -t nfs -rw $remote_ip:$remote_dir /mnt/
