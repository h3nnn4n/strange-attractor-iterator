#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <png.h>
#include <stdint.h>

#include "color.h"

void populatePal(_color *pallete){
    _color col;
    int size,i,r,g,b;
    char limbo[256];
    FILE *pal=fopen("pals/ultimate_feel.ppm","rt");
    if(pal==NULL){
        printf("ohshishishishish\n");
        exit(1);
    }

    fgets(limbo,255,pal);
    fgets(limbo,255,pal);
    fgets(limbo,255,pal);

    fscanf(pal,"%d\n",&size);
    size=255;

    if(size>0 && pal!=NULL){
        for(i=0;i<size;i++){
            fscanf(pal,"%d%d%d\n",&r,&g,&b);
            col.r=(double)r;
            col.g=(double)g;
            col.b=(double)b;
            memcpy(&pallete[i],&col,sizeof(_color));
        }
    }
    fclose(pal);
}

_color getPalMem(double p,_color *pal){
    int size=255;
    _color col;
    memcpy(&col,&pal[(int)((p*size)+0.5)],sizeof(_color));
    return col;
}

_color getHue(double h){	 // THis shifts thru the rgb color space. Very neat.
    _color col;
    h*=6.0;
    int hi=(int)h;
    double hf=h-hi;
    switch(hi){
        case 0:
            col.r=1.0;
            col.g=hf;
            col.b=0.0;
            break;
        case 1:
            col.r=1.0-hf;
            col.g=1.0;
            col.b=0.0;
            break;
        case 2:
            col.r=0.0;
            col.g=1.0;
            col.b=hf;
            break;
        case 3:
            col.r=0.0;
            col.g=1.0-hf;
            col.b=1.0;
            break;
        case 4:
            col.r=hf;
            col.g=0.0;
            col.b=1.0;
            break;
        case 5:
            col.r=1.0;
            col.g=0.0;
            col.b=1.0-hf;
            break;
    }

    //~ col.r=1-col.r;col.g=1-col.g;col.b=1-col.b; // Invert the colors

    return col;
}

_color getGrad2(double p){	 // Shifts from color one to color two
    _color col,c1,c2;
    c1.r =  82 / 255.0;
    c1.g = 181 / 255.0;
    c1.b = 126 / 255.0;

    c2.r = 192 / 255.0;
    c2.g = 133 / 255.0;
    c2.b = 152 / 255.0;

    c1.r=1-c1.r;c1.g=1-c1.g;c1.b=1-c1.b;
    c2.r=1-c2.r;c2.g=1-c2.g;c2.b=1-c2.b;

    if(p>1){
        p=p-((int)p);
    }

    p=sqrt(p);	// This gives a different change in the colors

    col.r=c1.r+p*(c2.r-c1.r);
    col.g=c1.g+p*(c2.g-c1.g);
    col.b=c1.b+p*(c2.b-c1.b);

    return col;
}

_color getPal(double p){	 // Get the colors from a file. Slow enough that make snails get respected.
    _color col;
    int size,i,r,g,b;
    char lal[256];
    FILE *pal=fopen("pals/sunrise.ppm", "rt");

    fgets(lal,255,pal);
    fgets(lal,255,pal);
    fgets(lal,255,pal);

    fscanf(pal,"%d\n",&size);

    p=p*size;

    if(p>0){
        for(i=0;i<p;i++){
            fscanf(pal,"%d\n%d\n%d\n",&r,&g,&b);
        }
    }else{
        fscanf(pal,"%d\n%d\n%d\n",&r,&g,&b);
    }

    col.r=r/255.0;
    col.g=g/255.0;
    col.b=b/255.0;

    fclose(pal);
    return col;
}

_color invert_color(_color col){	 // Invert the colors.
    col.r=255-col.r;
    col.g=255-col.g;
    col.b=255-col.b;
    return col;
}

/*
 * The function below was taken from http://www.lemoda.net/c/write-png/
 *
 */
int save_png_to_file (_color *bitmap, int screenx, int screeny, const char *path){
    FILE * fp;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    size_t x, y;
    png_byte ** row_pointers = NULL;
    /* "status" contains the return value of this function. At first
       it is set to a value which means 'failure'. When the routine
       has finished its work, it is set to a value which means
       'success'. */
    int status = -1;
    /* The following number is set by trial and error only. I cannot
       see where it it is documented in the libpng manual.
       */
    int pixel_size = 3;
    int depth = 8;

    fp = fopen (path, "wb");
    if (! fp) {
        goto fopen_failed;
    }

    png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
        goto png_create_write_struct_failed;
    }

    info_ptr = png_create_info_struct (png_ptr);
    if (info_ptr == NULL) {
        goto png_create_info_struct_failed;
    }

    /* Set up error handling. */

    if (setjmp (png_jmpbuf (png_ptr))) {
        goto png_failure;
    }

    /* Set image attributes. */

    png_set_IHDR (png_ptr,
            info_ptr,
            screenx,
            screeny,
            depth,
            PNG_COLOR_TYPE_RGB,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT);

    /* Initialize rows of PNG. */

    row_pointers = png_malloc (png_ptr, screeny * sizeof (png_byte *));
    for (y = 0; y < screeny; ++y) {
        png_byte *row = 
            png_malloc (png_ptr, sizeof (uint8_t) * screenx * pixel_size);
        row_pointers[y] = row;
        for (x = 0; x < screenx; ++x) {
            pixel_t pixel;

            pixel.red   = (uint8_t) bitmap[x + y * screenx].r;
            pixel.green = (uint8_t) bitmap[x + y * screenx].g;
            pixel.blue  = (uint8_t) bitmap[x + y * screenx].b;

            *row++ = pixel.red;
            *row++ = pixel.green;
            *row++ = pixel.blue;
        }
    }

    /* Write the image data to "fp". */

    png_init_io (png_ptr, fp);
    png_set_rows (png_ptr, info_ptr, row_pointers);
    png_write_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    /* The routine has successfully written the file, so we set
       "status" to a value which indicates success. */

    status = 0;

    for (y = 0; y < screeny; y++) {
        png_free (png_ptr, row_pointers[y]);
    }
    png_free (png_ptr, row_pointers);

png_failure:
png_create_info_struct_failed:
    png_destroy_write_struct (&png_ptr, &info_ptr);
png_create_write_struct_failed:
    fclose (fp);
fopen_failed:
    return status;
}
