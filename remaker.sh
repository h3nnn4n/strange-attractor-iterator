#!/bin/bash


fspec=gooderson.txt
num_files=4

total_lines=$(wc -l <${fspec})
((lines_per_file = (total_lines + num_files - 1) / num_files))

split --lines=${lines_per_file} ${fspec} xyzzy.

echo "Total lines     = ${total_lines}"
echo "Lines  per file = ${lines_per_file}"
wc -l xyzzy.*

for i in xyzzy.*
do
    {
        echo $i
        for i in `cat gooderson.txt`
        do
            ./cliff $i $i.good
        done
    } &
done

