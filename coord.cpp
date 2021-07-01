#include <math.h>
#include <iostream>

float x = 50;
float y = 0;
float l1 = 50;
float l2 = 50;
float d = 100; //a gép szélessége


float get_l1(float x, float y) {
	float l1= sqrt( pow(x,2) + pow(y,2) );
	return l1;
}

float get_l2(float x, float y) {
	float l2= sqrt( pow(d-x,2) + pow(y,2) );
	return l2;
}

float get_y(float l1, float l2) {
	float y= sqrt( (pow(l2,2)/(pow(d,2) - 2*d) ) - pow(l1,2) );
	return y;
}

float get_x(float l1, float l2) {
	float x = sqrt(pow(l1,2)-pow(get_y(l1, l2),2));
}


int main(int argc, char* argv[]) {

	if (argc > 1) {
		x= atof(argv[1]);
		y= atof(argv[2]);
		std::cout << "lx: " << get_x(l1,l2) << "\n";
		std::cout << "ly: " << get_y(l1,l2) << "\n";
	}
return 0;
}
