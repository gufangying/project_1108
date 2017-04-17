#!/bin/bash
FLAGS=-lpthread
g++ -shared -fPIC LWZSocket.cpp -o liblwzsocket.so ${FLAGS}
