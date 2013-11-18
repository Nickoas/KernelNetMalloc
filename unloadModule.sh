#!/bin/sh

module="NetMalloc"

rmmod ./$module.ko $* || exit 1