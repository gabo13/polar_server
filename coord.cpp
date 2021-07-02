#include <math.h>
#include <iostream>
#include <cassert>
using namespace std;

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
float get_x(float l1, float l2) {
	//float x = sqrt(pow(l1,2)-pow(get_y(l1, l2),2));
    float x = (pow(d,2)+pow(l1,2)-pow(l2,2))/(2*d);
    return x;
}
float get_y(float l1, float l2) {
	//float y= sqrt( (pow(l2,2)/(pow(d,2) - 2*d) ) - pow(l1,2) );
	float y = sqrt(pow(l1,2)-pow(get_x(l1,l2),2));
    return y;


}



template <typename T>
void print(T t) {
    
    cout << t << "\n";
}
void test() {
    assert(get_l1(50,0)==50);
    assert(get_l1(0,50)==50);
    assert(get_l1(0,0)==0);
    
    assert(get_l2(50,0)==50);
    assert(get_l2(100,50)==50);
    assert(get_l2(100,0)==0);
    
    assert(get_x(0,100)==0);
    assert(get_x(100,0)==100);
    assert(get_x(50,50)==50);
    assert(get_x(100,100)==50);
    
    assert(get_y(0,100)==0);
    assert(get_y(100,0)==0);
    assert(get_y(50,50)==0);
    
    
    print("Test complite\n");
}
int main(int argc, char* argv[]) {
    print(get_x(55,55));
    print(get_y(55,55));
    test();
    
    
    
    
    
    cout << "Exit\n";
    return 0;
}
