#ifndef __interpolation_hpp__
#define __interpolation_hpp__
#include <math.h>
float diff(float a, float b);
float linearInterpol_gety(float x1,float y1,float x2,float y2,float step);
float linearInterpol_getx(float x1,float y1, float x2, float y2,float step);
void linearInterpol(float x1, float y1, float x2, float y2, float step, void (*fp)(float, float));

#endif //__interpolation_h__
