#include <stdio.h>
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

    params.a = p_interval.mina + p * (p_interval.maxa - p_interval.mina);
    params.b = p_interval.minb + p * (p_interval.maxb - p_interval.minb);
    params.c = p_interval.minc + p * (p_interval.maxc - p_interval.minc);
    params.d = p_interval.mind + p * (p_interval.maxd - p_interval.mind);

    return params;
}

_parameters_interval get_random_interval(){
    _parameters_interval p_interval;

    p_interval.mina = drand48() * 4.0 - 2.0;       // Randomly chooses the values to be used as parameter.
    /*p_interval.maxa = drand48() * 4.0 - 2.0;*/

    p_interval.minb = drand48() * 4.0 - 2.0;
    /*p_interval.maxb = drand48() * 4.0 - 2.0;*/

    p_interval.minc = drand48() * 4.0 - 2.0;
    /*p_interval.maxc = drand48() * 4.0 - 2.0;*/

    p_interval.mind = drand48() * 4.0 - 2.0;
    /*p_interval.maxd = drand48() * 4.0 - 2.0;*/

    p_interval.maxa = p_interval.mina;
    p_interval.maxb = p_interval.minb;
    p_interval.maxc = p_interval.minc;
    p_interval.maxd = p_interval.mind;

    int r = rand() % 4;

    switch (r) {
        case 0:
            p_interval.maxa = p_interval.mina + (drand48() - 0.5) * .75;
            break;
        case 1:
            p_interval.maxb = p_interval.minb + (drand48() - 0.5) * .75;
            break;
        case 2:
            p_interval.maxc = p_interval.minc + (drand48() - 0.5) * .75;
            break;
        case 3:
            p_interval.maxd = p_interval.mind + (drand48() - 0.5) * .75;
            break;
    }

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

    double x , y , z , w ,
           xn, yn, zn, wn,
           a , b , c , d;

    a = params.a;
    b = params.b;
    c = params.c;
    d = params.d;

    x = (drand48() - 0.5) * 4.0;
    y = (drand48() - 0.5) * 4.0;
    z = (drand48() - 0.5) * 4.0;
    w = (drand48() - 0.5) * 4.0;

    for(j = 0 ; j < img_conf.iters ; j++){

        // Macro for the equations. Equations are in equations.h
        // It can also be set in the CFLAGS
        X_EQUATION
        Y_EQUATION
        Z_EQUATION
        W_EQUATION

        x = xn;
        y = yn;

        if(j < img_conf.skipIters)
            continue;

        if(useBounds == 0){
            if(x < bounds->minx){
                bounds->minx = x;
            }if(y < bounds->miny){
                bounds->miny = y;
            }if(x > bounds->maxx){
                bounds->maxx = x;
            }if(y > bounds->maxy){
                bounds->maxy = y;
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

    return;
}
