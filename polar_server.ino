#include <AccelStepper.h>
#include <MultiStepper.h>
#include "machine.hpp"

/****
-----2021.03.25. 18:00-----
* Parancsok:
* G00 gyorsjárat
* G01
* C00
* C01
* G90
* G91

* Változók:
* X= x pozíció mmben a rajzlap sarkától (mm)
* Y= y pozíció mmben a rajzlap sarkától (mm)
* A= a motorA hosszának változtatása (mm)
* B= a motorB hosszának változtatása (mm)
* F= előtolás (sebesség mm/sec)

pl.: G01 G90 X100 Z100
****/
#define DEBUG

#define PCOUNT 6 //paraméterek száma
#define PLENGTH 10 //paraméterek hossza
#define WAIT_TIME 5000; // ennyi idő után alszik (ms)

const static String PROMPT = "ready>";
const int cmd_length = 50;
const char cmd_interminator = 10;
const char cmd_separator = ' ';
char cmd_buff[cmd_length+1];
const static char* CMD_G00 = "G00"; // gyorsjárat x y paraméter
const static char* CMD_G01 = "G01"; // rajzol x y paraméter
const static char* CMD_C00 = "C00"; // gyorsjárat a b paraméter
const static char* CMD_C01 = "C01"; // rajzol a b paraméter
const static char* CMD_G90 = "G90"; // abszolút koordináta megadás
const static char* CMD_G91 = "G91"; // inkrementális koordináta megadás
const static char* CMD_SET = "SET"; // változó megadás

const static char CMD_X = 'X'; // X KOORDINÁTA
const static char CMD_Y = 'Y'; // Y KOORDINÁTA
const static char CMD_A = 'A'; // A KOORDINÁTA
const static char CMD_B = 'B'; // B KOORDINÁTA
const static char CMD_F = 'F'; // F ELŐTOLÁS

const static char* HELP = "HELP";
const static char* POWERON = "PWRON";
const static char* POWEROFF = "PWROFF";

static char inCmds[PCOUNT][PLENGTH]; // parameterek
static bool prompt_enable = true;

Machine machine;

char ch = 0;
void clearCmdBuff() {
  for (int i =0; i<cmd_length; i++) {
    cmd_buff[i] = 0;
  }
}
void clearParams() {
  for (int p=0; p<PCOUNT; p++)
    for(int pl=0; pl< PLENGTH; pl++) {
      inCmds[p][pl] = 0;
    }
}
void prompt(bool print) {
  if (print)
    Serial.print(PROMPT);
}
bool com_read(char* buff) { // Beolvasás a soros portról
  bool new_cmd = false;
  int buff_pos = 0;
  clearCmdBuff();
  clearParams();
  prompt(prompt_enable);
  prompt_enable = false;
  if (Serial.available() > 0) { 
    while(true) {
      char ch = Serial.read();
      if(ch == 10 ) {
        break;
      }
      buff[buff_pos] = ch;
      buff_pos += 1;
    }
    new_cmd = true;
    //Serial.println("Bussy");
    #ifdef DEBUG
    Serial.print("\nReceive: |");
    Serial.print(cmd_buff);
    Serial.println('|');
    #endif
    delay(500);
  } else {
    delay(1000);
  }
  return new_cmd;
}
char com_parse(char* buff) { // paraméterek megkeresése
  int buff_pos = 0;
  int par_pos = 0;
  int par = 0;

  while(buff[buff_pos] != 0) {
    inCmds[par][par_pos] = buff[buff_pos];
    buff_pos++;
    par_pos++;
    if (buff[buff_pos] == ' ') {
      par++;
      par_pos = 0;
      buff_pos++;
    }

  }
  return par+1;

}

void impl_g00() {
  #ifdef DEBUG
  Serial.println("    G00 parancs futtatva");
  #endif
  machine.penUp();
}
void impl_g01() {
  #ifdef DEBUG
  Serial.println("    G01 parancs futtatva");
  #endif
  machine.penDown();
}
void impl_c00() {
  #ifdef DEBUG
  Serial.println("    C00 parancs futtatva");
  #endif
  machine.penUp();
}
void impl_c01() {
  #ifdef DEBUG
  Serial.println("    C01 parancs futtatva");
  #endif
  machine.penDown();
}
void impl_g90() {
  #ifdef DEBUG
  Serial.println("    G90 parancs futtatva");
  #endif
}
void impl_g91() {
  #ifdef DEBUG
  Serial.println("    G91 parancs futtatva");
  #endif
}
void impl_set() {
  #ifdef DEBUG
  Serial.println("    SET parancs futtatva");
  #endif
  machine.setZero(225, 533);
}
void com_exec(int param_count) { // parancsok futtatása
  #ifdef DEBUG
  Serial.println("com_exec run");
  #endif
  if(param_count > PCOUNT) {
    Serial.println("Error: Tul sok parameter");
    return;
  }
  //void (*exec_fncPtr)();
  for (int i = 0; i<param_count; i++) {
  #ifdef DEBUG
    Serial.print(" Param-");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(inCmds[i]);
    Serial.println(';');
  #endif
    if(strcmp(inCmds[i], CMD_G00)== 0)
    {        //G00
      impl_g00();    
    } else if(strcmp(inCmds[i], CMD_G01)== 0)
    { //G01
      impl_g01();
    } else if(strcmp(inCmds[i], CMD_C00)== 0)
    { //C00
      impl_c00();
    } else if(strcmp(inCmds[i], CMD_C01)== 0)
    { //C01
      impl_c01();
    } else if(strcmp(inCmds[i], CMD_G90)== 0)
    { //G90
      impl_g90();
    } else if(strcmp(inCmds[i], CMD_G91)== 0)
    { //G91
      impl_g91();
    } else if(strcmp(inCmds[i], CMD_SET)== 0)
    { //SET
      impl_set();
    } else if(strcmp(inCmds[i], HELP)== 0)
    {
      Serial.println("HELP:");
      Serial.println("G00 G01 C00 C01 G90 G91 SET PWRON PWROFF");
    } else if(strcmp(inCmds[i], POWERON)== 0)
    {
      machine.powerOn();
    } else if(strcmp(inCmds[i], POWEROFF)== 0)
    {
      machine.powerOff();
    } else if(inCmds[i][0] == CMD_A)    // CMD_A
    {
      Serial.print("A value: ");
      Serial.println(atof(&inCmds[i][1]));
      machine.setA(atof(&inCmds[i][1]));
    } else if(inCmds[i][0] == CMD_B)    //CMD_B
    {
      Serial.print("B value: ");
      Serial.println(atof(&inCmds[i][1]));
      machine.setB(atof(&inCmds[i][1]));
    } else if(inCmds[i][0] == CMD_X)    //CMD_X
    {
      Serial.print("X value: ");
      Serial.println(atof(&inCmds[i][1]));
      machine.setX(atof(&inCmds[i][1]));
    } else if(inCmds[i][0] == CMD_Y)    //CMD_Y
    {
      Serial.print("Y value: ");
      Serial.println(atof(&inCmds[i][1]));
      machine.setY(atof(&inCmds[i][1]));
    } else if(inCmds[i][0] == CMD_F)    //CMD_F
    {
      machine.setF(atof(&inCmds[i][1]));
      Serial.print("F value: ");
      Serial.println(atof(&inCmds[i][1]));
    } else
    {
      Serial.print("Unknown command: ");
      Serial.println(inCmds[i]);
      return;
    }
  }
  machine.run();
  prompt_enable = true;
}
void setup() {
  Serial.begin(9600);
  Serial.print("Printer ON! Baud: ");
  Serial.println(9600);
  machine.print();
}
void loop() {
  if(com_read(cmd_buff)){
    int params = com_parse(cmd_buff);
    com_exec(params);
  }
  //Serial.println("New loop");
  
}
