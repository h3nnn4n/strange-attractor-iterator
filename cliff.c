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

    //populatePal(pal);
    //if(pal==NULL){
    //    fprintf(stderr,"NULL pointer crap!\n");
    //    return 1;
    //}

    screenx=1600/1.0;	 // The resolution of the image
    screeny=1200/1.0;

    frames=5800;	 // How many frames the image will have.
    skipIters=10;	 // Skips the first n cycles before drawing to the file
    iters=25000; 	 // Total iterations
    sens=0.025/2.25;	 // The brightness. Higher is brighter. The bigger the number frames, the smaller this value sould be

    //~ frames=5000;
    //~ iters=5000;
    //~ sens=0.5;

    //~ minx=-0.1;
    //~ maxx=1.0;
    //~ miny=0.9;
    //~ maxy=1.2;

    if(argc==3){	 // If the second parameter will be used as name if there is one. Useful for scripting
        strcpy(name,argv[2]);
        sprintf(fname,"%s.ppm",name);
    }else{
        sprintf(name,"name");	// Else if this will be used as name
        sprintf(fname,"%s.ppm",name);
    }

    if(argc>1){
        srand48(atoi(argv[1]));	 // Uses the first parameter as seed if there is one.
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
    /*
    for(i=0;i<screeny;i++){
        for(j=0;j<screenx;j++){
            bitmap[i*screenx+j].r=((1.0-(double)(j/screenx)))*frames*iters;
            bitmap[i*screenx+j].g=(double)(i/screeny)*frames*iters;
            bitmap[i*screenx+j].b=(((double)(i/screeny)+(double)(j/screenx))/2.0)*frames*iters;
        }
    }*/

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
                //~ xn=sin(x*b)+cos(y*c)+a*sin(w*b)+b*sin(a);
                //~ yn=cos(x*b)+cos(y*c)+a*cos(w*b)+b*cos(a);
                //~ wn=c*cos(log(a)*x)+d*sin(a*y)-cos(w*a);

                //xn=a*cos(x*b)+b*sin(y*c)+c*cos(w*d)+d*sin(z*a)+a;//+abs(a*(sin((b+y)*(y+c))));
                //yn=a*sin(x*b)+b*cos(y*c)+c*sin(w*d)+d*cos(z*a)+b;//+(b*(sin(w*w)));
                //wn=a*cos(x*b)+b*sin(y*c)+c*cos(w*d)+d*sin(z*a)+c;//+(c*(sin(z*z)));
                //zn=a*sin(x*b)+b*cos(y*c)+c*sin(w*d)+d*cos(z*a)+d;//+(d*(sin(x*x)));

                //xn=a*sin(x*b)+b*cos(y*c)+c*sin(x*a+y*b)-c*cos((x*y)*a)+log(2+cos(exp(y)-a));
                //yn=a*cos(x*b)+b*sin(y*c)+c*cos(x*a+y*b)-a+sin((x*y)*d)-log(2+sin(exp(x)+b));

                //xn=(sin(x*a*sin(c*y))+b)-fabs(cos(y*b*(cos(d*x))))-exp(c);
                //yn=(cos(y*a*sin(c*x))+a)-fabs(sin(x*b*(cos(d*y))))-exp(a);

                //xn=b*sin(a*exp(x))+c*cos(d*y+a);
                //yn=c*cos(b*exp(y))+a*sin(c*x+d);

                //xn=sin(a*w)+c*cos(b*x)+a*(w-y);
                //yn=sin(b*x)+d*cos(a*y)+b;
                //wn=c*(sin(j*M_PI/3600))/2.0;

                //~ xn=(sin(a*y)+c*cos(a*x))*cos(abs(pow((c),2)));
                //~ xn=pow(x*cos(a*x+b)+a,b)+c*cos(a*x);
                //~ yn=pow(y*cos(c*y+d)+c,d)+d*cos(b*y);
                //~ yn=(sin(b*x)+d*cos(b*y))*sin(abs(pow((b),2)));

                //~ if(mode==1){	// Here are the equations, uncomment then to be used.
                //~ xn=(sin(a*y)+c*cos(a*x))+sin(y);
                //~ yn=(sin(b*x)+d*cos(b*y))+cos(x);
                //~ }else if(mode==2){
                //~ xn=cos(x*a)+c*cos(y*b);
                //~ yn=sin(x*c)+sin(y*d);
                //~ }else if(mode==3){
                //~ xn=sin(x*a)-sin(y*a)-c;
                //~ yn=cos(y*b)+cos(x*b)+d;
                //~ }else if(mode==4){
                //~ xn+=(c*cos(y*d))+b*sin(y*b);
                //~ yn+=a*(a-sin(x*d))+d*cos(x*b);
                //~ }else if(mode==5){
                //xn=cos(a*x+sin(d*y))-b*(a*cos(y+d*x)-a*y)+M_PI;
                //yn=cos(b*y+sin(c*x))+a*(b*cos(x+c*y)-2);
                //~ }else if(mode==6){
                //~ xn=y*cos(y*a-x*b)-c*sin(y*d);
                //~ yn=sin(x*c-y*d)+a*cos(x*b);
                //~ }else if(mode==7){
                //~ xn=y*sin(x*a)-sin(y*a)+c/d*(cos(a*x+y*b));
                //~ yn=sin(b*x)+d*cos(b*y)+x/a*(sin(b*x+y*d));
                //~ }else if(mode==8){
                //~ xn=d*sin(a*x)-sin(b*y);
                //~ yn=c*cos(a*x)+cos(b*y);
                //~ }else if(mode==9){ // Secretely awesome!!!!!!!!!!!!!!!1
                //~ xn=b*sin(c*x)-sin(b*y)-(b-d*(d+b)*sin(x));
                //~ yn=a*cos(c*x)+cos(b*y)-(a-d*(c+a)*cos(y));
                //~ }else if(mode==10){
                //~ xn=d*cos(a*x)-y/cosh(x*a+y*b)*c;
                //~ yn=c*cos(a*x)+x/cosh(y*c+x*b)*d;
                //~ }else if(mode==11){
                //~ xn=d*cos(a*x)-b*sin(a*y)+cos(x*a+y*b)*c;
                //~ yn=c*cos(a*x)+b*cos(a*x)+sin(y*c+x*b)*d;
                //~ }else if(mode==12){
                //~ xn=a*sin(x*y*b);
                //~ yn=c*cos(d*x);
                //~ }else if(mode==13){
                //~ xn=a*sin(x*y*b)+y*a;
                //~ yn=c*cos(d*x)+x;
                //~ }else if(mode==14){
                //~ xn=sin(a*y)-z*cos(b*(x))+y+cos(w*a);
                //~ yn=z*sin(c*x)-cos(d*sin(cos(y)))+c*sin(w*b-c);
                //~ wn=c*(sin(j*M_PI/3600))/2.0;
                //~ zn=d*cos(x*b+c)-sin(y*b-a)*w;
                //~ }else if(mode==15){
                //~ xn=cos(a*z)+sin(b*y)-cos(c*x);
                //~ yn=sin(b*z)+cos(c*y)-sin(d*x);
                //~ zn=a*sin(b+x)+c*cos(d+y);
                //~ }else if(mode==16){
                //~ xn=a*sin(b*y)+c*sin(x*y/a);
                //~ yn=b*cos(c*z)+d*cos(z*w/b);
                //~ zn=c*sin(d*w)+a*sin(w*cos(b*y+1));
                //~ wn=d*cos(a*x)+b/(sin(z/d-cos(w-b)+sin(a*x)));
                //~ }else if(mode==17){
                //~ xn=sin(a*y)-z*cos(b*x);
                //~ yn=z*sin(c*x)-cos(d*y);
                //~ zn=sin(x*a)*c+b-cos(a*x);
                //~ }else if(mode==18){
                //~ xn=sin(a*y)-x*cos(b*abs(x))+y;
                //~ yn=z*sin(c*x)-cos(d*abs(y))+x;
                //~ zn=sin(x);
                //~ }else if(mode==19){
                //~ }else if(mode==20){
                //~ }else if(mode==21){
                //xn=sin(a*y)+cos(b*y)-sin(c*y)+sin(d*y-x)-sin(a*y*cos((b-a)*sin(b*x)));
                //yn=cos(a*x)-sin(b*x)+cos(c*x)-cos(d*x/a)+abs(sin(a+x*x*cos((a+y*sin(x+d)))));
                //~ }else if(mode==22){
                //~ xn=sin(a*y)+cos(b*y)-sin(c*y)+sin(d*y-x)-cos(a*y*cos((b-a)*sin(b*x)))+sin(c*(sin(j*M_PI/3600))/2.0*b-x)*c;
                //~ yn=cos(a*x)-sin(b*x)+cos(c*x)-cos(d*x/a)+sin(a+x*cos((a+y*sin(x+d))))-cos(c*d-y)*a;
                //~ }else if(mode==23){
                //~ xn=sin(a*y)+sin(b*y)-cos(c*y)+sin(d*y-x)-cos(a*y*sin((b-a)*sin(b*x)))+sin(a-y*b-x)-(c-a);
                //~ yn=cos(a*x)-cos(b*x)+sin(c*x)-cos(d*x/a)+sin(a+x*cos((a+y*sin(x+d))))-cos(c-x*d-y)+(b-d);
                //~ }else if(mode==24){
                //xn=cos(a*y)+sin(b*y)-sin(c*y)+cos(d*y-x)-b*cos(a*y+sin((b-a)*sin(b*x)))+y*(sin((b+c)*y)*(y-1.0))+b*sin(a-y*b-x)-(c-a);
                //yn=cos(a*x)-sin(b*x)+sin(c*x)-cos(d*x-y)+d*sin(a+x*cos((a+y*sin(x+d)))*sin(a+cos(x-y/2.3)))-a*cos(c-x*d-y)+(b-d);
                //~ }else if(mode=25){
                xn=cos(a*y)-cos(a*y)+sin(c*y)-sin(d*y)+cos(a*x+b)+sin((d-c)*x)+a-b;
                yn=cos(b*x)+cos(b*x)-sin(d*x)+sin(c*x)+cos(c*y+d)+cos((a-b)*y)+c-d;

                //xn=cos(a*y)-cos(a*y)+sin(c*y)-sin(d*y)+cos(a*x+b)+sin((d-c)*x)+b;
                //yn=cos(b*x)+cos(b*x)-sin(d*x)+sin(c*x)+cos(c*y+d)+cos((a-b)*y)+d;
                //~ }
                //~ }else if(mode=26){
                //~ xn+=(c*cos(y*d))+b*sin(y*b)-cos(y*y/x);
                //~ yn+=(sin(c*x))-cos(d*(y+a+sin(x)))-sin(x*y/a);
                //~ }
                //~ printf("x=%f\t%f\n",xn,yn);
                //~ }

                //~ shipwrecked

                x=xn;
                y=yn;
                w=wn;
                z=zn;

                //~ xn=0;
                //~ yn=0;
                //~ zn=0;
                //~ wn=0;

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

    //~ sprintf(tmp,"feh %s.png",name);
    //~
    //~ if(argc==1){
    //~ system(tmp);
    //~ }
    return EXIT_SUCCESS;
}
