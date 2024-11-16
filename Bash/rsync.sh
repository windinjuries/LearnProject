#!/bin/bash
local_dir=/home/book/Project/MontorSystem/backend
#local_dir=/home/book/Project/MontorSystem/backend
remote_dir=/home/orangepi/rsync
exclude_dir=./rsync_exclude.txt
remote_user=orangepi
# phone
# remote_ip=192.168.1.5
# route machine
remote_ip=192.168.2.14
python3 ./rsync.py ${remote_user} ${remote_ip} ${local_dir} ${remote_dir} ${exclude_dir}
