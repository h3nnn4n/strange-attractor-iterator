all: cliff.c
	gcc -Ofast -free -m64 -mtune=native -mfpmath=sse -msse4.2 -lm cliff.c -o cliff
