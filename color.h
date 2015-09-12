#ifndef __cliff_color
#define __cliff_color

#include <stdint.h>

typedef struct {
    double r, g, b;
} _color;

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} pixel_t;

_color pal[256];

int populatePal(_color *pallete);

int save_png_to_file(_color *bitmap, int screenx, int screeny, const char *path);

_color getPalMem(double p,_color *pal);
_color getHue(double h);
_color getGrad2(double p);
_color getPal(double p);

_color invert_color(_color col);

#endif /* __cliff_color */
