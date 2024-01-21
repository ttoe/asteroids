#!/bin/bash

set -xe

INCLUDE=$(pkg-config --cflags --libs raylib)
CFLAGS="-Wall -Wextra -Wpedantic -O0"

clang -std=c99 -o main main.c player.c $INCLUDE $CFLAGS

./main

