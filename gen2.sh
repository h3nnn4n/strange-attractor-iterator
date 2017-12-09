#!/bin/bash

for i in $(seq 201 400)
do
./cliff $i $i > /dev/null 2> /dev/null
echo -e "$i"
done
