CC=gcc
CFLAGS=-Ofast -lm

all: cliff.c
	$(CC) $(CFLAGS) -o cliff cliff.c

.PHONY: clean clean_bin clean_images
clean:
	-@rm cliff core *.png *.ppm 2>/dev/null || true

clean_images:
	-@rm *.png *.ppm 2>/dev/null || true

clean_bin:
	-@rm cliff core 2>/dev/null || true
