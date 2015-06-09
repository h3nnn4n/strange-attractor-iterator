typedef struct{
    double r,g,b;
}_color;

_color pal[256];

int populatePal(_color *pallete){
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
    int i,size=255;
    _color col;
    memcpy(&col,&pal[(int)((p*size)+0.5)],sizeof(_color));
    return col;
}

_color getHue(double h){	 // THis shifts thru the rgb color space. Very neat.
    _color col;
    h*=6.0;
    int hi=(int)h;
    double hf=h-hi;
    //~ switch(hi){
    //~ case 0:
    //~ col.r=1.0;
    //~ col.g=hf;
    //~ col.b=0.0;
    //~ break;
    //~ case 1:
    //~ col.r=1.0-hf;
    //~ col.g=1.0;
    //~ col.b=0.0;
    //~ break;
    //~ case 2:
    //~ col.r=0.0;
    //~ col.g=1.0;
    //~ col.b=hf;
    //~ break;
    //~ case 3:
    //~ col.r=0.0;
    //~ col.g=1.0-hf;
    //~ col.b=1.0;
    //~ break;
    //~ case 4:
    //~ col.r=hf;
    //~ col.g=0.0;
    //~ col.b=1.0;
    //~ break;
    //~ case 5:
    //~ col.r=1.0;
    //~ col.g=0.0;
    //~ col.b=1.0-hf;
    //~ break;
    //~ }
    switch(hi){
        case 0:
            col.r=0.0;
            col.g=sqrt(hf);
            col.b=0.7;
            break;
        case 1:
            col.r=0.2+hf/2.0;
            col.g=0.2;
            col.b=0.7;
            break;
        case 2:
            col.r=0.5;
            col.g=0.3;
            col.b=hf/2.0;
            break;
        case 3:
            col.r=0.25;
            col.g=hf;
            col.b=0.7245;
            break;
        case 4:
            col.r=hf/2.0;
            col.g=0.247;
            col.b=0.8632;
            break;
        case 5:
            col.r=0.57;
            col.g=0.157;
            col.b=1.0-hf/2;
            break;
    }

    //~ col.r=1-col.r;col.g=1-col.g;col.b=1-col.b; // Invert the colors

    return col;
}

_color getGrad2(double p){	 // Shifts from color one to color two
    _color col,c1,c2;
    c1.r = 82	/255.0;
    c1.g = 181	/255.0;
    c1.b = 126	/255.0;

    c2.r = 192	/255.0;
    c2.g = 133	/255.0;
    c2.b = 152	/255.0;

    c1.r=1-c1.r;c1.g=1-c1.g;c1.b=1-c1.b;
    c2.r=1-c2.r;c2.g=1-c2.g;c2.b=1-c2.b;

    if(p>1){
        p=p-((int)p);
    }

    p=sqrt(p);	// This gives a different change in the colors
    //~ p=log10f(p+25);

    //~ if(((int)p)%2==0 && p>1){
    //~ if(p>1){
    //~ p=p-((int)p+1);
    //~ }
    //~ }else{
    //~ if(p>1){
    //~ p=p-((int)p);
    //~ }
    //~ }



    col.r=c1.r+p*(c2.r-c1.r);
    col.g=c1.g+p*(c2.g-c1.g);
    col.b=c1.b+p*(c2.b-c1.b);

    return col;
}

_color getPal(double p){	 // Get the colors from a file. Slow enough that make snails get respected.
    _color col;
    int size,i,r,g,b;
    char lal[256];
    FILE *pal=fopen("pals/ultimate_feel.ppm", "rt");

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

    //~ printf("%d %d %d\n",r,g,b);

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
