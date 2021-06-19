#include <math.h>

void intermolation_with_y(float start_x, float start_y, float end_x, float end_y, float &curr_x, float &curr_y, float delta) {
  curr_x = start_x;
  curr_y = start_y;
  
  while(curr_x != end_x) {
    
    curr_y = ((curr_x-start_x)/(end_x-start_x))*(end_y-start_y)+start_y;
  }
}
