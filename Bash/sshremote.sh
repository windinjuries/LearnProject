#!/bin/bash
# phone
# ip=192.168.2.12
# route machine
ip=192.168.130.54
user=orangepi
if [[ $# -eq 1 ]]; then
    ip=$1
fi
echo ssh to connect client: ${user}@${ip} ...
ssh ${user}@${ip}
