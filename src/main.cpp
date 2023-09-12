#include <Arduino.h>
#include <PSX.h>

#define dataPin   10 
#define cmdPin    11  
#define attPin    12  
#define clockPin  13 

// Static instantiation of the library
PSX psx;

// Variables to hold the controller state and error code
PSX::PSXDATA PSXdata;
int PSXerror;

void moveForward();
void moveBackward();
void moveRight();
void moveLeft();
void stop();
void printData();

void setup() {
  //Setup the PSX library
  psx.setupPins(dataPin, cmdPin, attPin, clockPin, 10);
  psx.config(PSXMODE_ANALOG);
  
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  // Setup serial communication
  Serial.begin(9600);
}

void loop() {
  //moveForward();
  //moveBackward();
  //moveRight();
  //moveLeft();
  PSXerror = psx.read(PSXdata);
  printData();
  if(PSXdata.JoyRightY > 200){
    digitalWrite(3, HIGH);
  }
  else if(PSXdata.JoyRightY < 50){
    digitalWrite(4, HIGH);
  }
  else{
    stop();
  }
  if(PSXdata.JoyLeftY > 200){
    digitalWrite(5, HIGH);
  }
  else if(PSXdata.JoyLeftY < 50){
    digitalWrite(2, HIGH);
  }
  else{
    stop();
  }
}

void moveForward(){
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
}

void moveBackward(){
  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
}

void moveRight(){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
}

void moveLeft(){
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
}

void stop(){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void printData(){
  Serial.print(PSXdata.JoyLeftX);
  Serial.print("   ");
  Serial.print(PSXdata.JoyRightX);
  Serial.print("   ");
  Serial.print(PSXdata.JoyLeftY);
  Serial.print("   ");
  Serial.println(PSXdata.JoyRightY);
}