#!/bin/bash

for i in $(seq 601 800)
do
./cliff $i $i > /dev/null 2> /dev/null
echo -e "$i"
done
