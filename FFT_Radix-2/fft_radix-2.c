#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <stdbool.h>

/* Choose N complex input values (type double) in input.txt.
 * For example with N = 8, the input in form of (real,imaginary) can be specified as
 * (0,0) (0.707,0) (1,0) (0.707,0) (0,0) (-0.707,0) (-1,0) (-0.707,0)
 * which is a discrete time sinus function between 0 and 2pi.
 */
#define N 8

#ifndef M_PI
#define M_PI 3.1416
#endif
