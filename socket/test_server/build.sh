#!/bin/bash

bin="test.bin"

#lib目录
libdir=../

if [ -e ${bin} ];then
	rm ${bin}
	echo "rm old bin"
fi

g++ main.cpp -I../ -llwzsocket -L${libdir} -Wl,-rpath,${libdir} -o ${bin}

if [ -e ${bin} ];then
	./${bin}
fi
