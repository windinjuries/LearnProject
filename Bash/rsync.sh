#!/bin/bash
local_dir=~/Desktop/LearnProject
remote_dir=/home/orangepi/rsync/
remote_user=orangepi
remote_ip=192.168.31.119
exclude_dir=".git/"
rsync -a -vvv -h --delete  --exclude ${exclude_dir} ${local_dir} ${remote_user}@${remote_ip}:${remote_dir} 
