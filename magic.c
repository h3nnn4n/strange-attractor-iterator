#include <stdlib.h>
#include <math.h>

#include "magic.h"
#include "color.h"
#include "equations.h"



void cliff(_parameters params, _image_opt img_conf, _color *bitmap, _bounds *bounds, int useBounds, _color col){
    int    j, k,
           xi, yi;

    double x , y ,
           xn, yn,
           a , b , c , d,
           lowx, lowy, highx, highy;

    k = 0;

    lowx  = 0.0;
    lowy  = 0.0;
    highx = 0.0;
    highy = 0.0;

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

        if(k++ == 0){
            lowx  = x;
            lowy  = y;
            highx = x;
            highy = y;
        }

        if(useBounds == 0){
             if(x < lowx){
                lowx = x;
            }if(y < lowy){
                lowy = y;
            }if(x > highx){
                highx = x;
            }if(y > highy){
                highy = y;
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

    /*printf("%f %f %f %f\n", lowx, lowy, highx, highy);*/

    if(useBounds == 0){
        bounds->minx = lowx ;
        bounds->miny = lowy ;
        bounds->maxx = highx;
        bounds->maxy = highy;
    }

    return;
}
