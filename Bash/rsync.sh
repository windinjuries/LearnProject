#!/bin/bash
local_dir=~/Project/ustreamer
remote_dir=/home/orangepi/ustreamer
remote_user=orangepi
# phone
remote_ip=192.168.1.5
# route machine
# remote_ip=192.168.130.54
exclude_dir=".git/"
rsync -a -vvv -h --delete --exclude ${exclude_dir} ${local_dir} ${remote_user}@${remote_ip}:${remote_dir}
