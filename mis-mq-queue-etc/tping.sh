#!/bin/bash
cnt=$1
i=0

while [ $i -lt $cnt ]
do
ping 192.168.144.103 -n 1
((i++))

sleep 1
echo ""
echo "cnt is $i"
echo ""
done
