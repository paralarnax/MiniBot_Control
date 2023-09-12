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

//Declaration prototypes of stop and debugging functions
void stop();
void printData();

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

void loop() {
  //Read data from PS2 controller
  PSXerror = psx.read(PSXdata);
  //printData();
  //Right motor control logic
  if(PSXdata.JoyRightY > 200){
    digitalWrite(RightMotorB, HIGH);
  }
  else if(PSXdata.JoyRightY < 50){
    digitalWrite(RightMotorF, HIGH);
  }
  else{
    stop();
  }
  //Left motor control logic
  if(PSXdata.JoyLeftY > 200){
    digitalWrite(LeftMotorB, HIGH);
  }
  else if(PSXdata.JoyLeftY < 50){
    digitalWrite(LeftMotorF, HIGH);
  }
  else{
    stop();
  }
}

//Function to stop all motors
void stop(){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

//Debugging function to check all PS2 controller joystick channels
void printData(){
  Serial.print(PSXdata.JoyLeftX);
  Serial.print("   ");
  Serial.print(PSXdata.JoyRightX);
  Serial.print("   ");
  Serial.print(PSXdata.JoyLeftY);
  Serial.print("   ");
  Serial.println(PSXdata.JoyRightY);
}