#!/bin/sh
        
module="NetMalloc_sys"
default_adress="127.0.0.1:12345"


if [ $# = 1 ];
then
    echo insmod $module with $1
    insmod ./$module.ko "server=$1"
else
    echo insmod $module with $default_adress
    insmod ./$module.ko "server=$default_adress"
fi