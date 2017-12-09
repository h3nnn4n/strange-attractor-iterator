#!/bin/bash


# icc -Ofast -parallel -march=native -mtune=native -mfpmath=sse cliff.c -o cliff && ./cliff 0 0 && sxiv 0.png RIP ICC
gcc -Ofast -parallel -march=native -mtune=native -mfpmath=sse cliff.c -o cliff && ./cliff 0 0 && sxiv 0.png
