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
#include "magic.h"

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

    img_conf.screenx     = 1920 / 1.0;                   // The resolution of the image
    img_conf.screeny     = 1080 / 1.0;

             offset      = 1000;

    img_conf.frames      = 25000;                         // How many frames the image will have.
    img_conf.skipIters   = 500;                          // Skips the first n cycles before drawing to the file
    img_conf.iters       = 10000;                         // Total iterations
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

    p_interval = get_random_interval();
    bounds     = init_bounds();

    printf("%s --- \n",name);

    k = 0;

    printf("Parameters are:\n");
    printf("a=%.3f to %.3f\n", cos(p_interval.mina) * 16, cos(p_interval.maxa) * 16);
    printf("b=%.3f to %.3f\n", cos(p_interval.minb) * 16, cos(p_interval.maxb) * 16);
    printf("c=%.3f to %.3f\n", cos(p_interval.minc) * 16, cos(p_interval.maxc) * 16);
    printf("d=%.3f to %.3f\n", cos(p_interval.mind) * 16, cos(p_interval.maxd) * 16);

    bitmap = (_color*) malloc (sizeof(_color) * img_conf.screenx * img_conf.screeny);

    _bounds bb;

    for(l = 0 ; l < 2 ; l++){
        if(l == 0)
            printf("Evaluating bondaries...\n");
        else if(l == 1)
            printf("Starting drawing and stuff...\n");

        for(i = 0 ; i < img_conf.frames ; ( l == 0 ? i += 10 : i++ )){
            p = (double) i / img_conf.frames;

            params = get_param_set_from_interval(p_interval, p);

            col = getPal(p);


            cliff(params, img_conf, bitmap, &bb, l, col);

            if ( k == 0 ){
                k++;
                bounds = bb;
            }

            if (l == 0) {
                bounds = update_boundaries(bounds, bb);
            }

            if( i % (img_conf.frames / 5) == 0 && l == 1)
                fprintf(stdout," -- %.2f%%\n", p * 100.0);
        }

        if(l == 0){
            bounds.minx *= 1.125;
            bounds.miny *= 1.125;
            bounds.maxx *= 1.125;
            bounds.maxy *= 1.125;

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

