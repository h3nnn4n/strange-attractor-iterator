#ifndef __cliff_magic
#define __cliff_magic

#include "color.h"

typedef struct {
    double a, b, c, d;
} _parameters;

typedef struct {
    double mina;
    double maxa;

    double minb;
    double maxb;

    double minc;
    double maxc;

    double mind;
    double maxd;
} _parameters_interval;

typedef struct {
    int frames, skipIters, iters,
        screenx, screeny;

    double sens;
} _image_opt;

typedef struct {
    double minx, maxx;
    double miny, maxy;
} _bounds;


void                 cliff(_parameters params, _image_opt img_conf, _color *bitmap, _bounds *bounds, int useBounds, _color col);
_parameters_interval get_random_interval();
_bounds              init_bounds();
_parameters          get_param_set_from_interval(_parameters_interval p_interval, double p);
_bounds              update_boundaries(_bounds a, _bounds b);

#endif /* __cliff_magic */
