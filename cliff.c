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
	
	_color *bitmap,col;
	
	//~ mode=14;	 // The equation to be used.
	
	screenx=1600/1;	 // The resolution of the image
	screeny=1200/1;	
	
	frames=7500;	 // How many frames the image will have.
	skipIters=1000;	 // Skips the first n cycles before drawing to the file
	iters=5000; 	 // Total iterations
	sens=0.05/1.0;	 // The brightness. Higher is brighter. The bigger the number frames, the smaller this value sould be
	
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
			
			x=0.0;
			y=0.0;
			w=0.0;
			z=0.0;
			
			//~ col=getHue(p);   	 // The coloring mode. THis used shifts the colors thru the RGB color space where at least one canal will be the maximum.
			col=getGrad2(p*25.0);	 // Shifts from one color to another. See color.h
			//~ col=getPal(p);   	 // Reads a gradient from a file. UTTERLY SLOW!!!!!!!!!!!!!!!!!!!!!1!! Dont dare to used it.
			
			for(j=0;j<iters;j++){
				//~ if(mode==1){	// Here are the equations, uncomment then to be used. 
					xn=sin(a*y)+c*cos(a*x);
					//~ yn=sin(b*x)+d*cos(b*y);
				//~ }else if(mode==2){
					//~ xn=cos(x*a)+cos(y*b);
					//~ yn=sin(x*c)+sin(y*d);
				//~ }else if(mode==3){
					//~ xn=sin(x*a)-sin(y*a)-c;
					yn=cos(y*b)+cos(x*b)+d;
				//~ }else if(mode==4){
					//~ xn=c*cos(y*d))+b*sin(y*b);
					//~ yn=a-sin(x*d))+d*cos(x*b);
				//~ }else if(mode==5){
					//~ xn=cos(a*x+sin(d*y))-b*(a*cos(y+d*x)-pow(a,y));
					//~ yn=cos(b*y+sin(c*x))+a*(b*cos(x+c*y)-pow(c,x));
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
					//~ xn=b*sin(c*x)-sin(b*y)-y/(d+b*sin(x));
					//~ yn=a*cos(c*x)+cos(b*y)-x/(c+a*cos(y));
				//~ }else if(mode==10){
					//~ xn=d*cos(a*x)-y/cosh(x*a+y*b)*c;
					//~ yn=c*cos(a*x)+x/cosh(y*c+x*b)*d;
				//~ }else if(mode==11){
					//~ xn=d*cos(a*x)-b*sin(a*y)/cosh(x*a+y*b)*c;
					//~ yn=c*cos(a*x)+b*cos(a*x)/cosh(y*c+x*b)*d;
				//~ }else if(mode==12){
					//~ xn=a*sin(x*y*b);
					//~ yn=c*cos(d*x);
				//~ }else if(mode==13){
					//~ xn=a*sin(x*y*b)+y*a;
					//~ yn=c*cos(d*x)+x;
				//~ }else if(mode==14){
					//~ xn=sin(a*y)-z*cos(b*(x))+y+cos(w*a);
					//~ yn=z*sin(c*x)-cos(d*sin(cos(y)))+x*sin(w*b-c);
					//~ wn=c*(sin(j*M_PI/3600))/2.0;
					//~ zn=d*cos(x*b+c)-sin(y*b-a)*b;
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
					//~ xn=a*sin(y-c)+y*cos(c)+d;
					//~ yn=b*cos(w-d)+w*sin(d)+a;
					//~ wn=c*sin(b+z)-z*cos(a)+b;
					//~ zn=d*cos(a*x)+x*sin(b)+sin(x-y+w-z);
				//~ }else if(mode==20){
					//~ xn=sin(a*y)+cos(c*x)+cos(c*b+x)+sin(a*a*y)+sin(x*cos(y*a)-c)-b;
					//~ yn=cos(b*y)-sin(d*x)-sin(d*a-y)-cos(x*x*d)-cos(a*sin(x*(x-d)));
				//~ }else if(mode==21){
					//~ xn=sin(a*y)+cos(b*y)-sin(c*y)+sin(d*y-x)-sin(a*y*cos((b-a)*sin(b*x)));
					//~ yn=cos(a*x)-sin(b*x)+cos(c*x)-cos(d*x/a)+sin(a+x*cos((a+y*sin(x+d))));
				//~ }else if(mode==22){
					//~ xn=sin(a*y)+cos(b*y)-sin(c*y)+sin(d*y-x)-cos(a*y*cos((b-a)*sin(b*x)))+sin(c*(sin(j*M_PI/3600))/2.0*b-x)*c;
					//~ yn=cos(a*x)-sin(b*x)+cos(c*x)-cos(d*x/a)+sin(a+x*cos((a+y*sin(x+d))))-cos(c*d-y)*a;
				//~ }else if(mode==23){
					//~ xn=sin(a*y)+sin(b*y)-cos(c*y)+sin(d*y-x)-cos(a*y*sin((b-a)*sin(b*x)))+sin(a-y*b-x)-(c-a);
					//~ yn=cos(a*x)-cos(b*x)+sin(c*x)-cos(d*x/a)+sin(a+x*cos((a+y*sin(x+d))))-cos(c-x*d-y)+(b-d);
				//~ }else if(mode==24){
					//~ xn=cos(a*y)+sin(b*y)-sin(c*y)+cos(d*y-x)-b*cos(a*y+sin((b-a)*sin(b*x)))+y*(sin((b+c)*y)*(y-1.0))+b*sin(a-y*b-x)-(c-a);
					//~ yn=cos(a*x)-sin(b*x)+sin(c*x)-cos(d*x-y)+d*sin(a+x*cos((a+y*sin(x+d)))*sin(a+cos(x-y/2.3)))-a*cos(c-x*d-y)+(b-d);
				//~ }else if(mode=25){
					//~ xn=cos(a*y)-cos(a*y)+sin(c*y)-sin(d*y)+cos(a*x+b)+y/5.0;
					//~ yn=cos(b*x)+cos(b*x)-sin(d*x)+sin(c*x)+cos(c*y+d)+x/5.0;
				//~ }
				//~ }else if(mode=26){
					//~ xn=(c*cos(y*d))+b*sin(y*b);
					//~ yn=(sin(c*x))-cos(d*(y+a));
					//~ }
				//~ }
				
				//~ shipwrecked
				
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
	fprintf(stdout,"minx=%.4f;\tmaxx=%.4f;\nminy=%.4f;\tmaxy=%.4f;\n",lowx+(lowx/25.0),highx+(highx/25.0),lowy+(lowy/25.0),highy+(highy/25.0));
	
	fclose(img);
	free(bitmap);
	
	sprintf(tmp,"convert %s %s.png",fname,name);
	system(tmp);
	
	sprintf(tmp,"rm %s",fname);
	system(tmp);
	
	sprintf(tmp,"feh %s.png",name);
	
	if(argc==1){
		system(tmp);
	}
	
	return EXIT_SUCCESS;
}
