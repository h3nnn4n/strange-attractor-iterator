#ifndef __cliff_color
#define __cliff_color

typedef struct {
    double r, g, b;
} _color;

_color pal[256];

int populatePal(_color *pallete);

_color getPalMem(double p,_color *pal);

_color getHue(double h);

_color getGrad2(double p);

_color getPal(double p);

_color invert_color(_color col);

#endif /* __cliff_color */
