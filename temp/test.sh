#!/bin/bash

if [ -f test.log ];then
rm test.log
fi

gcc -o main.exe  main.c  -lpthread
./main.exe > test.log
cat test.log | grep console | wc -l
cat test.log | grep uart    | wc -l
