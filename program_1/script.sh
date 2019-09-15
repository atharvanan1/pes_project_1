#!/bin/bash

gcc -std=c99 -Wall -Werror -o main main.c
if [[ -f "ProgramOne.out" ]]; then
	./main < input >> ProgramOne.out
else
	./main < input > ProgramOne.out 
fi
cat ProgramOne.out 
