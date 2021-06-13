#ifndef __machine__
#define __machine__
#include <AccelStepper.h>
#include <MultiStepper.h>

#define WAIT_TIME 5000; // ennyi idő után alszik (ms)

class Machine {
  private:
    const static int mStep_Per_Rev = 200;
    const static int mMM_Per_Rev = 32;
    int mWidth; //lépés
    int mHeight; //lépés
    float mStep_Per_MM = 6;
    int mEnablPin = 8;
    AccelStepper mA;
    AccelStepper mB;

  public:
    Machine(int width, int height); //(mm)
    void print();
    void run();
    void powerOff();
    void powerOn();
    void setX(float x);
};

Machine::Machine(int width = 450, int height =533) { //(mm)
        
        mWidth = width*6.25;
        mHeight = height*6.25;

        mA = AccelStepper(1,2,5);
        mB = AccelStepper(1,3,6);

    }
void Machine::print() {
      Serial.print("Machinw width: ");
      Serial.print(mWidth);
      Serial.print("\nMachinw height: ");
      Serial.println(mHeight);
    }
void Machine::run() {
  
}
void Machine::powerOff() {
  Serial.println("POWER OF");
}
void Machine::powerOn() {
  Serial.println("POWER ON");
}
void Machine::setX(float x){

}

#endif //__machine__
