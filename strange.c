#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "magic.h"
#include "color.h"
#include "equations.h"


double test(double *a, int len){
    double r = 0;
    for (int i = 0; i < len; ++i) {
        r += a[i];
        a[i] = -1;
    }
    return r;
}

void parameters_test(_parameters *p) {
    printf("%f %f %f %f\n", p->a, p->b, p->c, p->d);
    return;
}


double foo(_parameters params, _image_opt img_conf, _color *bitmap, _bounds *bounds, int useBounds, _color col){
    int    j,
           xi, yi;

    double x , y , z , w ,
           xn, yn, zn, wn,
           a , b , c , d;

    a = (drand48() - 0.5) * 4.0;
    b = (drand48() - 0.5) * 4.0;
    c = (drand48() - 0.5) * 4.0;
    d = (drand48() - 0.5) * 4.0;

    x = (drand48() - 0.5) * 4.0;
    y = (drand48() - 0.5) * 4.0;
    z = (drand48() - 0.5) * 4.0;
    w = (drand48() - 0.5) * 4.0;

    double p = 0;

    for(j = 0 ; j < img_conf.iters ; j++){

        // Macro for the equations. Equations are in equations.h
        // It can also be set in the CFLAGS
        X_EQUATION
        Y_EQUATION
        Z_EQUATION
        W_EQUATION

        x = xn;
        y = yn;

        p += x;

        if(j < img_conf.skipIters)
            continue;

        /*if(useBounds == 0){*/
            /*if(x < bounds->minx){*/
                /*bounds->minx = x;*/
            /*}if(y < bounds->miny){*/
                /*bounds->miny = y;*/
            /*}if(x > bounds->maxx){*/
                /*bounds->maxx = x;*/
            /*}if(y > bounds->maxy){*/
                /*bounds->maxy = y;*/
            /*}*/
        /*}else if(useBounds == 1){*/
            /*xi = ((x - bounds->minx) * img_conf.screenx / (bounds->maxx - bounds->minx));*/
            /*yi = ((y - bounds->miny) * img_conf.screeny / (bounds->maxy - bounds->miny));*/

            /*if(xi < img_conf.screenx && xi >= 0 && yi < img_conf.screeny && yi >= 0){*/
                /*bitmap[yi * img_conf.screenx + xi].r += col.r;*/
                /*bitmap[yi * img_conf.screenx + xi].g += col.g;*/
                /*bitmap[yi * img_conf.screenx + xi].b += col.b;*/
            /*}*/
        /*}*/
    }

    return p;
}

/*void cliff(_parameters params, _image_opt img_conf, _color *bitmap, _bounds *bounds, int useBounds, _color col){*/
    /*int    j,*/
           /*xi, yi;*/

    /*double x , y , z , w ,*/
           /*xn, yn, zn, wn,*/
           /*a , b , c , d;*/

    /*a = params.a;*/
    /*b = params.b;*/
    /*c = params.c;*/
    /*d = params.d;*/

    /*x = (drand48() - 0.5) * 4.0;*/
    /*y = (drand48() - 0.5) * 4.0;*/
    /*z = (drand48() - 0.5) * 4.0;*/
    /*w = (drand48() - 0.5) * 4.0;*/

    /*for(j = 0 ; j < img_conf.iters ; j++){*/

        /*// Macro for the equations. Equations are in equations.h*/
        /*// It can also be set in the CFLAGS*/
        /*X_EQUATION*/
        /*Y_EQUATION*/
        /*Z_EQUATION*/
        /*W_EQUATION*/

        /*x = xn;*/
        /*y = yn;*/

        /*if(j < img_conf.skipIters)*/
            /*continue;*/

        /*if(useBounds == 0){*/
            /*if(x < bounds->minx){*/
                /*bounds->minx = x;*/
            /*}if(y < bounds->miny){*/
                /*bounds->miny = y;*/
            /*}if(x > bounds->maxx){*/
                /*bounds->maxx = x;*/
            /*}if(y > bounds->maxy){*/
                /*bounds->maxy = y;*/
            /*}*/
        /*}else if(useBounds == 1){*/
            /*xi = ((x - bounds->minx) * img_conf.screenx / (bounds->maxx - bounds->minx));*/
            /*yi = ((y - bounds->miny) * img_conf.screeny / (bounds->maxy - bounds->miny));*/

            /*if(xi < img_conf.screenx && xi >= 0 && yi < img_conf.screeny && yi >= 0){*/
                /*bitmap[yi * img_conf.screenx + xi].r += col.r;*/
                /*bitmap[yi * img_conf.screenx + xi].g += col.g;*/
                /*bitmap[yi * img_conf.screenx + xi].b += col.b;*/
            /*}*/
        /*}*/
    /*}*/

    /*return;*/
/*}*/
