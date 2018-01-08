#ifndef STRANGE_H
#define STRANGE_H

#include "magic.h"
#include "color.h"
#include "equations.h"


void parameters_test(_parameters *p);
double test(double *a, int len);
double foo(_parameters params, _image_opt img_conf, _color *bitmap, _bounds *bounds, int useBounds, _color col);

//void cliff(_parameters params, _image_opt img_conf, _color *bitmap, _bounds *bounds, int useBounds, _color col);

#endif /* STRANGE_H */
