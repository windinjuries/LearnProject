#!/bin/bash
local_dir=~/Desktop/LearnProject
remote_dir=/home/orangepi/
remote_user=orangepi
# phone
remote_ip=192.168.2.12
# route machine
#remote_ip=192.168.130.54
exclude_dir=".git/"
rsync -a -vvv -h --delete  --exclude ${exclude_dir} ${local_dir} ${remote_user}@${remote_ip}:${remote_dir} 
local_dir=~/Desktop/streamer
remote_dir=/home/orangepi/
rsync -a -vvv -h --delete  --exclude ${exclude_dir} ${local_dir} ${remote_user}@${remote_ip}:${remote_dir} 
