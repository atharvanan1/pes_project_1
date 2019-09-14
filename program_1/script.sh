#!/bin/bash

gcc -std=c99 -Wall -Werror -o main main.c
./main < input > file
cat file
