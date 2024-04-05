#!/bin/bash
echo 'param count:' $#
echo 'param:' $*
rsync -av ~/Desktop/LearnProject/ orangepi@192.168.31.119:/home/orangepi/mnt/
