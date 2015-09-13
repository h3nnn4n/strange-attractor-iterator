#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "magic.h"
#include "color.h"
#include "equations.h"

_bounds update_boundaries(_bounds a, _bounds b){
    if ( b.minx < a.minx ) {
        a.minx = b.minx;
    }if ( b.miny < a.miny ) {
        a.miny = b.miny;
    }if ( b.maxx > a.maxx ) {
        a.maxx = b.maxx;
    }if ( b.maxy > a.maxy ) {
        a.maxy = b.maxy;
    }

    return a;
}

_parameters get_param_set_from_interval(_parameters_interval p_interval, double p){
    _parameters params;

    params.a = cos(p_interval.mina + p * (p_interval.maxa - p_interval.mina)) * 16.0;
    params.b = cos(p_interval.minb + p * (p_interval.maxb - p_interval.minb)) * 16.0;
    params.c = cos(p_interval.minc + p * (p_interval.maxc - p_interval.minc)) * 16.0;
    params.d = cos(p_interval.mind + p * (p_interval.maxd - p_interval.mind)) * 16.0;

    return params;
}

_parameters_interval get_random_interval(){
    _parameters_interval p_interval;

    p_interval.mina = acos( (drand48() * 4.0 - 2.0) / 16.0);       // Randomly chooses the values to be used as parameter.
    p_interval.maxa = acos( (drand48() * 4.0 - 2.0) / 16.0);

    p_interval.minb = acos( (drand48() * 4.0 - 2.0) / 16.0);
    p_interval.maxb = acos( (drand48() * 4.0 - 2.0) / 16.0);

    p_interval.minc = acos( (drand48() * 4.0 - 2.0) / 16.0);
    p_interval.maxc = acos( (drand48() * 4.0 - 2.0) / 16.0);

    p_interval.mind = acos( (drand48() * 4.0 - 2.0) / 16.0);
    p_interval.maxd = acos( (drand48() * 4.0 - 2.0) / 16.0);

    return p_interval;
}

_bounds init_bounds(){
    _bounds bounds;

    bounds.minx =  9999.0;
    bounds.miny =  9999.0;
    bounds.maxx = -9999.0;
    bounds.maxy = -9999.0;

    return bounds;
}

void cliff(_parameters params, _image_opt img_conf, _color *bitmap, _bounds *bounds, int useBounds, _color col){
    int    j,
           xi, yi;

    double x , y ,
           xn, yn,
           a , b , c , d;

    _bounds bb;

    bb = init_bounds();

    a = params.a;
    b = params.b;
    c = params.c;
    d = params.d;

    x = (drand48() - 0.5) * 4.0;
    y = (drand48() - 0.5) * 4.0;

    for(j = 0 ; j < img_conf.iters ; j++){

        X_EQUATION
        Y_EQUATION

        x = xn;
        y = yn;

        if(j < img_conf.skipIters)
            continue;

        if(useBounds == 0){
            if(x < bb.minx){
                bb.minx = x;
            }if(y < bb.miny){
                bb.miny = y;
            }if(x > bb.maxx){
                bb.maxx = x;
            }if(y > bb.maxy){
                bb.maxy = y;
            }
        }else if(useBounds == 1){
            xi = ((x - bounds->minx) * img_conf.screenx / (bounds->maxx - bounds->minx));
            yi = ((y - bounds->miny) * img_conf.screeny / (bounds->maxy - bounds->miny));

            if(xi < img_conf.screenx && xi >= 0 && yi < img_conf.screeny && yi >= 0){
                bitmap[yi * img_conf.screenx + xi].r += col.r;
                bitmap[yi * img_conf.screenx + xi].g += col.g;
                bitmap[yi * img_conf.screenx + xi].b += col.b;
            }
        }
    }

    if(useBounds == 0){
        memcpy(bounds, &bb, sizeof(_bounds));
    }

    return;
}
