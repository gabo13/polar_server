#ifndef __MACHINE_HPP__
#define __MACHINE_HPP__


#include <math.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Servo.h>
#include "interpolation.hpp"

//#define WAIT_TIME 5000; // ennyi idő után alszik (ms)

class Machine {
  private:
    const static int mStep_Per_Rev = 200;
    const static int mMM_Per_Rev = 32;
    int mWidth; //lépés
    int mHeight; //lépés
    float mStep_Per_MM = 6.25*8;
    int mEnablPin = 8;
    AccelStepper mA;
    AccelStepper mB;
    int mServoPin = 9;
    
    float positionsAB[2];
    float positionsXY[2];
    MultiStepper steppers;
    Servo pen;
    float F;
    bool statusONOFF = false;
    bool penDownPos = true;
    
  public:
    Machine(int width = 450, int height = 450); //(mm)
    void print();
    void run();
    void powerOff();
    void powerOn();
    void penUp();
    void penDown();

    void setX(float x);
    void setY(float y); 
    void setA(float a);
    void setB(float b);
    void setF(float f);
    void setZero(float x, float y);

    float calcA(float x, float y);
    float calcB(float x, float y);
    float calcX(float a, float b);
    float calcY(float a, float b);
};



#endif //__MACHINE_HPP__
