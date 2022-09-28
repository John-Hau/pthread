#!/usr/bin/bash


i=0

while [ $i -lt 1024 ]
do
   printf '\xff' >> tr.bin
   ((i++))
done

echo "done"
