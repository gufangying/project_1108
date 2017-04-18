#!/bin/bash

bin="test.bin"

if [ -e ${bin} ];then
	rm ${bin}
	echo "rm old bin"
fi

g++ main.cpp -I../socket/ -llwzsocket -L../socket -Wl,-rpath,../socket -o ${bin}

if [ -e ${bin} ];then
	./${bin}
fi
