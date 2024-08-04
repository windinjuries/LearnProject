#!/bin/bash
local_dir=~/Desktop/LearnProject
remote_dir=/home/orangepi/
remote_user=orangepi
# phone
# remote_ip=192.168.1.5
# route machine
remote_ip=192.168.2.14
exclude_dir=".git/" 
python3 ./sync.py ${remote_user} ${remote_ip} ${local_dir} ${remote_dir}
# rsync -a -vvv -h --delete --exclude ${exclude_dir} ${local_dir} ${remote_user}@${remote_ip}:${remote_dir}
