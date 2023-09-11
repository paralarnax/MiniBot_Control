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
  PSXerror = psx.read(PSXdata);
  if(PSXerror == PSXERROR_SUCCESS) {
      if(PSXdata.buttons & PSXBTN_UP) {
        Serial.println("Forward");
        moveForward();
      }
      if(PSXdata.buttons & PSXBTN_DOWN) {
        Serial.println("Backward");
        moveBackward();
      }
      if(PSXdata.buttons & PSXBTN_RIGHT) {
        Serial.println("Right");
        moveRight();
      }
      if(PSXdata.buttons & PSXBTN_LEFT) {
        Serial.println("LEFT");
        moveLeft();
      }
      else{
        Serial.println("STOP");
        stop();
      }
  } else {
    Serial.print("No success reading data. Check connections and timing.");
  }
}

void moveForward(){
  digitalWrite(2, HIGH);
  digitalWrite(5, HIGH);
}

void moveBackward(){
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
}

void moveRight(){
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
}

void moveLeft(){
  digitalWrite(5, HIGH);
  digitalWrite(3, HIGH);
}

void stop(){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}