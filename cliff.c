#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "color.h"

int main(int argc,char *argv[]){
    int 	screenx,screeny,
            i,j,k,l,
            xi,yi,
            mode,
            offset,
            iters,frames,skipIters;
    float	a,b,c,d,
            mina,minb,minc,mind,
            maxa,maxb,maxc,maxd,
            minx,maxx,miny,maxy,
            lowx,lowy,highx,highy,
            p,sens,
            xn,yn,zn,wn,
            x,y,z,w;
    char	name[257],fname[257],tmp[257];

    _color *bitmap,col,*pal;

    pal=(_color*)malloc(sizeof(_color)*255);

    screenx=1600/1.0;	 // The resolution of the image
    screeny=1200/1.0;

    offset = 1000;

    frames=5800;	 // How many frames the image will have.
    skipIters=500;	 // Skips the first n cycles before drawing to the file
    iters=25000; 	 // Total iterations
    sens=0.025/4.125;	 // The brightness. Higher is brighter. The bigger the number frames, the smaller this value sould be

    if(argc==3){	 // If the second parameter will be used as name if there is one. Useful for scripting
        strcpy(name,argv[2]);
        sprintf(fname,"%s.ppm",name);
    }else{
        sprintf(name,"name");	// Else if this will be used as name
        sprintf(fname,"%s.ppm",name);
    }

    if(argc>1){
        srand48(atoi(argv[1]) + offset);	 // Uses the first parameter as seed if there is one.
    }else{
        srand48(6);				 // Else use this one as seed. The seed determine the value generated as parameter.
    }

    printf("%s --- \n",name);

    FILE *img=fopen(fname,"wt");

    mina=acos( (drand48()*4.0-2.0)/16.0);	 // Randomly chooses the values to be used as parameter.
    maxa=acos( (drand48()*4.0-2.0)/16.0);

    minb=acos( (drand48()*4.0-2.0)/16.0);
    maxb=acos( (drand48()*4.0-2.0)/16.0);

    minc=acos( (drand48()*4.0-2.0)/16.0);
    maxc=acos( (drand48()*4.0-2.0)/16.0);

    mind=acos( (drand48()*4.0-2.0)/16.0);
    maxd=acos( (drand48()*4.0-2.0)/16.0);

    k=0;

    fprintf(img,"P3\n%d %d\n255\n",screenx,screeny);

    printf("Parameters are:\n");
    printf("a=%.3f to %.3f\n",cos(mina)*16,cos(maxa)*16);
    printf("b=%.3f to %.3f\n",cos(minb)*16,cos(maxb)*16);
    printf("c=%.3f to %.3f\n",cos(minc)*16,cos(maxc)*16);
    printf("d=%.3f to %.3f\n",cos(mind)*16,cos(maxd)*16);

    bitmap=(_color*)malloc(sizeof(_color)*screenx*screeny);

    for(l=0;l<2;l++){
        if(l==0)
            printf("Evaluating bondaries...\n");
        else if(l==1)
            printf("Starting drawing and stuff...\n");

        for(i=0;i<=(l==0?frames*0.10:frames);i++){
            p=i/(double)(l==0?frames*0.10:frames);

            a=cos(mina+p*(maxa-mina))*16.0;
            b=cos(minb+p*(maxb-minb))*16.0;
            c=cos(minc+p*(maxc-minc))*16.0;
            d=cos(mind+p*(maxd-mind))*16.0;

            //~ col=getHue(p);   	 // The coloring mode. THis used shifts the colors thru the RGB color space where at least one canal will be the maximum.
            //~ col=getGrad2(p*12.50);	 // Shifts from one color to another. See color.h
            col=getPal(p);   	 // Reads a gradient from a file. UTTERLY SLOW!!!!!!!!!!!!!!!!!!!!!1!! Dont dare to used it.
            //~ col=getPalMem(p,pal);   	 // Ultimate version of palete, now directly from the RAM. about 123152394582 times faster. More than enough

            x=(drand48()-0.5)*5.0;
            y=(drand48()-0.5)*5.0;
            w=(drand48()-0.5)*5.0;
            z=(drand48()-0.5)*5.0;

            for(j=0;j<iters;j++){

                xn = (a*cos((j*M_PI/180.0)*b+c)) + c*cos(a*x) + d*cos(b*y) + a*cos(y*x + a);
                yn = (b*sin((j*M_PI/180.0)*a+d)) + d*sin(b*y) + c*cos(a*x) + b*cos(y*x + b);

                x=xn;
                y=yn;
                w=wn;
                z=zn;

                if(j<skipIters)
                    continue;

                if(k++==0){
                    lowx=x;lowy=y;highx=x;highy=y;
                }

                if(l==0){
                    if(x<lowx){
                        lowx=x;
                    }if(y<lowy){
                        lowy=y;
                    }if(x>highx){
                        highx=x;
                    }if(y>highy){
                        highy=y;
                    }
                }else if(l==1){
                    xi=((x-minx)*screenx/(maxx-minx));
                    yi=((y-miny)*screeny/(maxy-miny));

                    if(xi<screenx && xi>=0 && yi<screeny && yi>=0){
                        bitmap[yi*screenx+xi].r+=col.r;
                        bitmap[yi*screenx+xi].g+=col.g;
                        bitmap[yi*screenx+xi].b+=col.b;
                    }
                }
            }
            if(i%(frames/5)==0 && l==1)
                fprintf(stdout," -- %.2f%%\n",p*100.0);
        }

        //~ minx=lowx-(lowx/25.0);
        //~ miny=lowy-(lowy/25.0);
        //~ maxx=highx+(highx/25.0);
        //~ maxy=highy+(highy/25.0);

        minx=lowx;
        miny=lowy;
        maxx=highx;
        maxy=highy;

        if(l==0){
            printf("Boundaries are:\n");
            printf("x %.3f to %.3f\n",minx,maxx);
            printf("y %.3f to %.3f\n",miny,maxy);
        }
    }

    for(i=0;i<screeny;i++){
        for(j=0;j<screenx;j++){
            col=bitmap[i*screenx+j];
            col.r=((1.0-exp(-sens*col.r))*255.0);
            col.g=((1.0-exp(-sens*col.g))*255.0);
            col.b=((1.0-exp(-sens*col.b))*255.0);

            col=invert_color(col);

            fprintf(img,"%d %d %d ",(int)col.r,(int)col.g,(int)col.b);
        }
        fputc('\n',img);
    }

    printf(" -------\n\n");
    //~ fprintf(stdout,"minx=%.4f;\tmaxx=%.4f;\nminy=%.4f;\tmaxy=%.4f;\n",lowx+(lowx/25.0),highx+(highx/25.0),lowy+(lowy/25.0),highy+(highy/25.0));
    fprintf(stdout,"minx=%.4f;\tmaxx=%.4f;\nminy=%.4f;\tmaxy=%.4f;\n",minx,maxx,miny,maxy);

    fclose(img);
    free(bitmap);

    sprintf(tmp,"convert %s %s.png",fname,name);
    system(tmp);

    sprintf(tmp,"rm %s",fname);
    system(tmp);

    return EXIT_SUCCESS;
}
