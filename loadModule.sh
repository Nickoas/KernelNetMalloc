#!/bin/sh
        
module="NetMalloc"

insmod ./$module.ko $* || exit 1
