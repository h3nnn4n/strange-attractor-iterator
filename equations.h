#ifndef X_EQUATION
#define X_EQUATION xn = pow(tanh(a * x), 2.0) + c * (1.0 / cosh(d * y)) + b * (1.0 * sin(a * x)) + cos((j / img_conf.iters) * d * M_PI) * a; // * (a * cos(((j / img_conf.iters) * 10.0 * M_PI) + z));
#endif

#ifndef Y_EQUATION
#define Y_EQUATION yn = pow(tanh(b * y), 2.0) + d * (1.0 / cosh(c * x)) + a * (1.0 * sin(c * y)) + sin((j / img_conf.iters) * c * M_PI) * b; // * (b * sin(((j / img_conf.iters) * 10.0 * M_PI) + w));
#endif

#ifndef W_EQUATION
#define W_EQUATION
#endif

#ifndef Z_EQUATION
#define Z_EQUATION
#endif
