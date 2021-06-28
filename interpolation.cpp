#include "interpolation.hpp"


float diff(float a, float b)
{
  return fabs(a-b);
}


float linearInterpol_gety(float x1,float y1,float x2,float y2,float step)

{
  float xn = x1+step;
  float yn = float(((xn-x1)/(x2-x1))*(y2-y1)+y1);
  return round(yn);
}


float linearInterpol_getx(float x1,float y1, float x2, float y2,float step)
{
  float yn = y1+step;
  float xn = ((yn-y1)/(y2-y1))*(x2-x1)+x1;
  return round(xn);
}


void linearInterpol(float x1, float y1, float x2, float y2, float step, void (*fp)(float, float))
{
  float xn=x1;
  float yn=y1;

  if (diff(x1,x2) >= diff(y1,y2)) //y=f(x)
  {
    if (x2<x1) step= -step;
     while(xn<x2)
     {
       yn = linearInterpol_gety(xn,yn,x2,y2,step);
       xn = xn+step;
       //std::cout << "xy: " << xn <<", "<< yn << "\n";
       fp(xn,yn);
     }
  } else // x= f(y)
  {
    if (y2<y1) step= -step;
     while(yn<y2)
     {
       xn = linearInterpol_getx(xn,yn,x2,y2,step);
       yn = yn+step;
       //std::cout << "xy: " << xn <<", "<< yn << "\n";
       fp(xn,yn);
     }
  }
}
