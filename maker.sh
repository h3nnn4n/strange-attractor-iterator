#!/bin/bash

./stopper.sh # Stops any instance that might be running
make clean  # *REMOVES* all the images in the current folder. You should  read the script to be *EXTRA* sure that you wont delete anything important.

make

./gen1.sh & # Each one of those script executes the ./cliff with a different seed 200 times
./gen2.sh &
./gen3.sh &
./gen4.sh &

