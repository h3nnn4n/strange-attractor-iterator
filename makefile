all: cliff.c
	gcc -Ofast -lm -o cliff cliff.c
#	gcc -Ofast -free -m64 -mtune=native -mfpmath=sse -msse4.2 -lm cliff.c -o cliff

icc:
	icc -Ofast -march=native -mtune=native -ip -ipo -parallel cliff.c -o cliff
