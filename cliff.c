/************************************************************************************
 *     Strange attractor iterator. This program iterates a set of equations,        *
 *     detects it's size and scale to a given resolution and saves it on a          *
 *     net-bpm image. After that convert (from ImageMagick) is called to convert    *
 *     the image into a png and the old one is removed.                             *
 *                                                                                  *
 *                                                                                  *
 *     Copyright (C) 2014-2015  Renan S. Silva                                      *
 *                                                                                  *
 *     This program is free software: you can redistribute it and/or modify         *
 *     it under the terms of the GNU General Public License as published by         *
 *     the Free Software Foundation, either version 3 of the License, or            *
 *     (at your option) any later version.                                          *
 *                                                                                  *
 *     This program is distributed in the hope that it will be useful,              *
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of               *
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                *
 *     GNU General Public License for more details.                                 *
 *                                                                                  *
 *     You should have received a copy of the GNU General Public License            *
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.        *
 *                                                                                  *
 ***********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "equations.h"
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

void cliff(_parameters params, _image_opt img_conf, _color *bitmap, _bounds *bounds, int useBounds, _color col);

int main(int argc, char *argv[]){
    int     i,j,k,l,
            offset;
    float   p;
    char    name[257],fname[257];

    _bounds              bounds;
    _image_opt           img_conf;
    _parameters          params;
    _parameters_interval p_interval;

    _color *bitmap, col;

    img_conf.screenx     = 1920 / 2.0;                   // The resolution of the image
    img_conf.screeny     = 1080 / 2.0;

             offset      = 1000;

    img_conf.frames      = 5800;                         // How many frames the image will have.
    img_conf.skipIters   = 500;                          // Skips the first n cycles before drawing to the file
    img_conf.iters       = 25000;                        // Total iterations
    img_conf.sens        = 0.025 / 4.125;                // The brightness. Higher is brighter. The bigger the number frames, the smaller this value sould be

    if(argc == 3){                              // If the second parameter will be used as name if there is one. Useful for scripting
        strcpy(name,argv[2]);
        sprintf(fname,"%s.png",name);
    }else{
        sprintf(name,"name");                   // Else if this will be used as name
        sprintf(fname,"%s.png",name);
    }

    if(argc > 1){
        srand48(atoi(argv[1]) + offset);        // Uses the first parameter as seed if there is one.
    }else{
        srand48(6);                             // Else use this one as seed. The seed determine the value generated as parameter.
    }

    printf("%s --- \n",name);

    p_interval.mina = acos( (drand48() * 4.0 - 2.0) / 16.0);       // Randomly chooses the values to be used as parameter.
    p_interval.maxa = acos( (drand48() * 4.0 - 2.0) / 16.0);

    p_interval.minb = acos( (drand48() * 4.0 - 2.0) / 16.0);
    p_interval.maxb = acos( (drand48() * 4.0 - 2.0) / 16.0);

    p_interval.minc = acos( (drand48() * 4.0 - 2.0) / 16.0);
    p_interval.maxc = acos( (drand48() * 4.0 - 2.0) / 16.0);

    p_interval.mind = acos( (drand48() * 4.0 - 2.0) / 16.0);
    p_interval.maxd = acos( (drand48() * 4.0 - 2.0) / 16.0);

    bounds.minx =  9999.0;
    bounds.miny =  9999.0;
    bounds.maxx = -9999.0;
    bounds.maxy = -9999.0;

    k = 0;

    printf("Parameters are:\n");
    printf("a=%.3f to %.3f\n", cos(p_interval.mina) * 16, cos(p_interval.maxa) * 16);
    printf("b=%.3f to %.3f\n", cos(p_interval.minb) * 16, cos(p_interval.maxb) * 16);
    printf("c=%.3f to %.3f\n", cos(p_interval.minc) * 16, cos(p_interval.maxc) * 16);
    printf("d=%.3f to %.3f\n", cos(p_interval.mind) * 16, cos(p_interval.maxd) * 16);

    bitmap = (_color*) malloc (sizeof(_color) * img_conf.screenx * img_conf.screeny);

    for(l = 0 ; l < 2 ; l++){
        if(l == 0)
            printf("Evaluating bondaries...\n");
        else if(l == 1)
            printf("Starting drawing and stuff...\n");

        for(i = 0 ; i <= (l==0 ? img_conf.frames * 0.10 :img_conf.frames) ; i++){     // The ternary operator is is used to run a smaller version of the code to get
            p = i / (double) (l==0 ? img_conf.frames * 0.10 : img_conf.frames);       // some boundaries for the image

            params.a = cos(p_interval.mina + p * (p_interval.maxa - p_interval.mina)) * 16.0;
            params.b = cos(p_interval.minb + p * (p_interval.maxb - p_interval.minb)) * 16.0;
            params.c = cos(p_interval.minc + p * (p_interval.maxc - p_interval.minc)) * 16.0;
            params.d = cos(p_interval.mind + p * (p_interval.maxd - p_interval.mind)) * 16.0;

            col = getPal(p);

            _bounds bb;

            cliff(params, img_conf, bitmap, &bb, l, col);

            if ( k++ == 0 ){
                bounds = bb;
            }

            if (l == 0) {
                 if ( bb.minx < bounds.minx ) {
                    bounds.minx = bb.minx;
                }if ( bb.miny < bounds.miny ) {
                    bounds.miny = bb.miny;
                }if ( bb.maxx > bounds.maxx ) {
                    bounds.maxx = bb.maxx;
                }if ( bb.maxy > bounds.maxy ) {
                    bounds.maxy = bb.maxy;
                }
            }

            if( i % (img_conf.frames / 5) == 0 && l == 1)
                fprintf(stdout," -- %.2f%%\n", p * 100.0);
        }

        if(l == 0){
            bounds.minx = bounds.minx * 1.25;
            bounds.miny = bounds.miny * 1.25;
            bounds.maxx = bounds.maxx * 1.25;
            bounds.maxy = bounds.maxy * 1.25;

            printf("Boundaries are:\n");
            printf("x %.3f to %.3f\n", bounds.minx, bounds.maxx);
            printf("y %.3f to %.3f\n", bounds.miny, bounds.maxy);
        }
    }

    for(i = 0 ; i < img_conf.screeny ; i++){
        for(j = 0 ; j < img_conf.screenx ; j++){
            col = bitmap[i * img_conf.screenx + j];

            col.r = ((1.0 - exp( - img_conf.sens * col.r)) * 255.0);
            col.g = ((1.0 - exp( - img_conf.sens * col.g)) * 255.0);
            col.b = ((1.0 - exp( - img_conf.sens * col.b)) * 255.0);

            col = invert_color(col);

            bitmap[i * img_conf.screenx + j] = col;
        }
    }

    printf(" -------\n\n");

    fprintf(stdout,"minx=%.4f;\tmaxx=%.4f;\nminy=%.4f;\tmaxy=%.4f;\n", bounds.minx,
                                                                       bounds.maxx,
                                                                       bounds.miny,
                                                                       bounds.maxy );

    save_png_to_file(bitmap, img_conf.screenx, img_conf.screeny, fname);

    free(bitmap);


    return EXIT_SUCCESS;
}

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
