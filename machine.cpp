#include "machine.hpp"

Machine::Machine(int width = 450, int height =450) { //(mm)
        
        mWidth = width;
        mHeight = height;
        /*
         * Motor A
         * PIN 8 Enable pin
         * PIN 2 Step pin
         * PIN 5 Dir pin
         * 
         * Motor B
         * PIN 8 Enable pin
         * PIN 3 Step pin
         * PIN 6 Dir pin
         *
         * Motor C
         * PIN 8 Enable pin
         * PIN 4 Step pin
         * PIN 7 Dir pin
        */
        pinMode(mEnablPin,OUTPUT);
        mA = AccelStepper(1,3,6);
        mB = AccelStepper(1,2,5);
        mA.setEnablePin(mEnablPin);
        mB.setEnablePin(mEnablPin);
        mB.setPinsInverted(false,false, true);
        mA.setPinsInverted(true,false, true);
        setF(400);
        steppers.addStepper(mA);
        steppers.addStepper(mB);

        
        
        
}


void Machine::print() {
      Serial.print("Machine width: ");
      Serial.print(mWidth);
      Serial.print("mm\nMachine height: ");
      Serial.print(mHeight);
      Serial.println("mm");
}


void Machine::run() {
  long moveToSteps[2];
  Serial.print("X:");
  Serial.print(positionsXY[0]);
  Serial.print("mm Y:");
  Serial.print(positionsXY[1]);
  Serial.print("mm A:");
  Serial.print(positionsAB[0]);
  Serial.print("mm B:");
  Serial.print(positionsAB[1]);
  Serial.println("mm");
  moveToSteps[0] = (long)(positionsAB[0]*mStep_Per_MM);
  moveToSteps[1] = (long)(positionsAB[1]*mStep_Per_MM);
  steppers.moveTo(moveToSteps);
  steppers.runSpeedToPosition();
  delay(100); 
}
void Machine::powerOff() {
  Serial.println("POWER OFF");
  statusONOFF = false;
  if(pen.attached()) pen.detach();
  mA.disableOutputs();
  mB.disableOutputs();
  
}
void Machine::powerOn() {
  Serial.println("POWER ON");
  statusONOFF = true;
  delay(100);
  pen.attach(mServoPin);
  mA.enableOutputs();
  mB.enableOutputs();
  //x=225 y=332 a tábla közepe
  setZero(225, 533);
  
}

void Machine::penUp()
{
  //if(penDownPos)
  {
    pen.write(90);
    Serial.println("pen is Up");
    //penDownPos = false;
  }
  delay(500);
}
void Machine::penDown()
{
  //if(!penDownPos)
  {
    pen.write(0);
    Serial.println("pen is Down");
    //penDownPos = true;
  }
  delay(500);
}
void Machine::setZero(float x, float y) {
  setX(x);
  setY(y);
  mA.setCurrentPosition((long)(positionsAB[0]*mStep_Per_MM));
  mB.setCurrentPosition((long)(positionsAB[1]*mStep_Per_MM));
  Serial.print("A stepper current position: ");
  Serial.println(mA.currentPosition());
  Serial.print("B stepper current position: ");
  Serial.println(mB.currentPosition());
  
}
void Machine::setX(float x){
  positionsXY[0] = x;
  positionsAB[0] = calcA(positionsXY[0],positionsXY[1]);
  positionsAB[1] = calcB(positionsXY[0],positionsXY[1]);
}
void Machine::setY(float y){
  positionsXY[1] = y;
  positionsAB[0] = calcA(positionsXY[0],positionsXY[1]);
  positionsAB[1] = calcB(positionsXY[0],positionsXY[1]);
}
void Machine::setA(float a){              //mm
  positionsAB[0] = a;
  positionsXY[0] = calcX(positionsAB[0],positionsAB[1]);
  positionsXY[1] = calcY(positionsAB[0],positionsAB[1]);
}
void Machine::setB(float b) {             //mm
  positionsAB[1] = b;
  positionsXY[0] = calcX(positionsAB[0],positionsAB[1]);
  positionsXY[1] = calcY(positionsAB[0],positionsAB[1]);
}
void Machine::setF(float f) {
  F = f;
  mA.setMaxSpeed(f);
  mB.setMaxSpeed(f);
}
float Machine::calcA(float x, float y) {
  float a= sqrt( pow(x,2) + pow(y,2) );
  #ifdef debug
  Serial.print("a = ");
  Serial.println(a);
  #endif
  return a;
}

float Machine::calcB(float x, float y) {
  float b= sqrt( pow(mWidth-x,2) + pow(y,2) );
  #ifdef debug
  Serial.print("b = ");
  Serial.println(b);
  #endif
  return b;
}
float Machine::calcX(float a, float b) {
    //float x = (pow(mWidth,2)+pow(a,2)-pow(b,2))/(2*mWidth); //ezzel működött
    float x = (pow(b,2)-pow(a,2)-pow(mWidth,2))/(2*mWidth);
    #ifdef debug
    Serial.print("x = ");
    Serial.println(x);
    #endif
    return x;
}
float Machine::calcY(float a, float b) {
  float y = sqrt(pow(a,2)-pow(calcX(a,b),2));
  #ifdef debug
  Serial.print("y = ");
  Serial.println(y);
  #endif
    return y;
}
