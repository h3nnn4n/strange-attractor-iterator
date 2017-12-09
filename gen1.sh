#!/bin/bash

for i in $(seq 0 200)
do
./cliff $i $i > /dev/null 2> /dev/null
echo -e "$i"
done
