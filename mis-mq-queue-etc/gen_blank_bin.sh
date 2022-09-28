#!/bin/bash
rm -rf blank.bin
i=0
while [ $i -lt $1 ]
do

#echo -n -e "\xff"  >> blank.bin
echo -n -e "\xff"  >> EE16KB.bin
((i++))

done
echo "done"


