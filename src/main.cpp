/*
    Name:         MiniBot_Control
    Descr:        Basic programm for control motors with joysticks
    Version:      0.1   
    Author:       Paralarnax
    Date:         12.09.2023     
    Annotation:   This programm was developed for prototype of MiniBot,
                  which have l298n driver (bad decision). We will replace
                  this driver in production version and also add basic servo
                  gripper and line sensors.
*/

//Add main lidraries and configuration file
#include <Arduino.h>
#include <PSX.h>
#include <config.h>

// Static instantiation of the library
PSX psx;

// Variables to hold the controller state and error code
PSX::PSXDATA PSXdata;
int PSXerror;

byte motorSpeed[] = {0, 0, 0, 0};
byte motorSlowdown = 0;

void setup() {
  //Setup the PSX library
  psx.setupPins(dataPin, cmdPin, attPin, clockPin, 10);
  psx.config(PSXMODE_ANALOG);
  //Motor pins as output
  pinMode(LeftMotorB,  OUTPUT);
  pinMode(LeftMotorF,  OUTPUT);
  pinMode(RightMotorB, OUTPUT);
  pinMode(RightMotorF, OUTPUT);
  //Setup serial communication
  Serial.begin(9600);
}

void speedControl(){
  //Read data from PS2 controller
  PSXerror = psx.read(PSXdata);
  if(PSXdata.buttons & PSXBTN_R2) {
    if(PSXdata.JoyLeftX >= 128){
      motorSlowdown = map(PSXdata.JoyLeftX, 128, 255, 1, 127);
      motorSpeed[1] = 255;
      motorSpeed[3] = 0;
      motorSpeed[2] = (motorSlowdown * 2);
    }
    if(PSXdata.JoyLeftX <= 126){
      motorSlowdown = map(PSXdata.JoyLeftX, 0, 126, 127, 1);
      motorSpeed[1] = 0;
      motorSpeed[3] = 255;
      motorSpeed[0] = (motorSlowdown * 2);
    }
    if(PSXdata.JoyLeftX == 127){
      motorSpeed[1] = 255;
      motorSpeed[3] = 255;
      motorSpeed[2] = 0;
      motorSpeed[0] = 0;
      motorSlowdown = 0;
    }
  }
  else if(PSXdata.buttons & PSXBTN_L2) {
    if(PSXdata.JoyLeftX >= 128){
      motorSlowdown = map(PSXdata.JoyLeftX, 128, 255, 1, 127);
      motorSpeed[2] = 0;
      motorSpeed[0] = 255;
      motorSpeed[3] = (motorSlowdown * 2);
    }
    if(PSXdata.JoyLeftX <= 126){
      motorSlowdown = map(PSXdata.JoyLeftX, 0, 126, 127, 1);
      motorSpeed[2] = 255;
      motorSpeed[0] = 0;
      motorSpeed[1] = (motorSlowdown * 2);
    }
    if(PSXdata.JoyLeftX == 127){
      motorSpeed[1] = 0;
      motorSpeed[3] = 0;
      motorSpeed[2] = 255;
      motorSpeed[0] = 255;
      motorSlowdown = 0;
    }
  }
  else{
    motorSpeed[0] = 0;
    motorSpeed[1] = 0;
    motorSpeed[2] = 0;
    motorSpeed[3] = 0;
    motorSlowdown = 0;
  }
}

//Function to stop all motors
void motorSetSpeed(){
  analogWrite(LeftMotorB, motorSpeed[0]);
  analogWrite(LeftMotorF, motorSpeed[1]);
  analogWrite(RightMotorB, motorSpeed[2]);
  analogWrite(RightMotorF, motorSpeed[3]);
}

//Debugging function to check all PS2 controller joystick channels
void printCyberdeck(){
  Serial.print(PSXdata.JoyLeftX);
  Serial.print("   ");
  Serial.print(PSXdata.JoyRightX);
  Serial.print("   ");
  Serial.print(PSXdata.JoyLeftY);
  Serial.print("   ");
  Serial.print(PSXdata.JoyRightY);
  Serial.print("   ");
  if(PSXdata.buttons & PSXBTN_R2) {
    Serial.print("R2, ");
  }
  if(PSXdata.buttons & PSXBTN_L2) {
    Serial.print("L2, ");
  }
  Serial.println("");
}

void printMotorData(){
  Serial.print(motorSpeed[0]);
  Serial.print("   ");
  Serial.print(motorSpeed[1]);
  Serial.print("   ");
  Serial.print(motorSpeed[2]);
  Serial.print("   ");
  Serial.print(motorSpeed[3]);
  Serial.print("   ");
  Serial.print(motorSlowdown);
}

void loop() {
  speedControl();
  //printCyberdeck();
  printMotorData();
  motorSetSpeed();
}