#!/bin/bash
ip=192.168.31.119
user=orangepi
if [[ $# -eq 1 ]]; then
    ip=$1
fi
echo ssh to connect client: ${user}@${ip} ...
ssh ${user}@${ip}
