#!/bin/bash

set -xe

INCLUDE=$(pkg-config --cflags --libs raylib)
CFLAGS="-Wall -Wextra -Wpedantic -O0"
CFILES=src/*.c

clang -std=c99 -o main $CFILES $INCLUDE $CFLAGS

./main

