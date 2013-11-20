#!/bin/sh
        
module="NetMalloc"
default_adress="192.168.0.1:12345"


if [ $# = 1 ];
then
    insmod ./$module.ko "server=$1"
    echo $module launch on $1
else
    insmod ./$module.ko "server=$default_adress"
    echo $module launch on $default_adress
fi