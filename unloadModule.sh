#!/bin/sh

module="NetMalloc_sys"

rmmod ./$module.ko $* || exit 1