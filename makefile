CC=gcc
CFLAGS=-Ofast -lm -lpng
FILES=cliff.c color.c
BINS=cliff

all: cliff.c
	$(CC) $(CFLAGS) -o $(BINS) $(FILES)

.PHONY: clean clean_bin clean_images
clean:
	-@rm $(BINS) core *.png *.ppm 2>/dev/null || true

clean_images:
	-@rm *.png *.ppm 2>/dev/null || true

clean_bin:
	-@rm $(BINS) core 2>/dev/null || true
