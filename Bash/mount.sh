#!/bin/bash
local_dir=/home/orangepi/mnt
remote_dir=/home/fengzhishang/Project/CarSystem/Server
remote_ip=192.168.2.52
mount -t nfs -rw $remote_ip:$remote_dir /mnt/
