/*
 *Throttle - (944,1944)
 *Pitch - (1196,1694)
 *Yaw - (1248,1752) 
 *Roll - (1296,1800)
 
 *Throttle = Up or Down (Channel 3)
 *Pitch = Forward or Backward (Channel 2)
 *Yaw = Rotation (Channel 4)
 *Roll = Left or Right (Channel 1)
 */

#include "PinChangeInterrupt.h"
#include <Servo.h>

//Variables
const int throttlePin = 2; volatile unsigned long throttlePWMStart = 0; volatile int throttleTemp = 1000; 
const int pitchPin = 3; volatile unsigned long pitchPWMStart = 0; volatile int pitchTemp = 1000;
const int yawPin = 4; volatile unsigned long yawPWMStart = 0; volatile int yawTemp = 1000;
const int rollPin = 5; volatile unsigned long rollPWMStart = 0; volatile int rollTemp = 1000;

//Transmitter Ranges
int throttleStart = 944; int throttleEnd = 1944;
int pitchStart = 1196; int pitchEnd = 1694;
int yawStart = 1248; int yawEnd = 1752;
int rollStart = 1296; int rollEnd = 1800;

//Define Motors
Servo esc1; int esc1Pin = 7;

void setup() {
  Serial.begin(115200);
  
  //Set the pins as input
  pinMode(throttlePin, INPUT);
  pinMode(pitchPin, INPUT);
  pinMode(yawPin, INPUT);
  pinMode(rollPin, INPUT);

  //Using the Arduino PCINT Library, it is a pin change library
  attachPCINT(digitalPinToPCINT(throttlePin), readThrottle, CHANGE); 
  attachPCINT(digitalPinToPCINT(pitchPin), readPitch, CHANGE);
  attachPCINT(digitalPinToPCINT(yawPin), readYaw, CHANGE); 
  attachPCINT(digitalPinToPCINT(rollPin), readRoll, CHANGE); 

  //Attach and Arm ESCs
  esc1.attach(esc1Pin, 1000, 2000); 
  esc1.writeMicroseconds(1000); //Zero throttle for stopping
  delay(5000); //Wait 5 seconds for arming
}

void loop() {
  //Set no interrupt to not corrupt data
  noInterrupts();
  
  //Fetching value from interrupts
  int throttleValue = throttleTemp;
  throttleValue = generatePWM(throttleValue, throttleStart, throttleEnd, 1000, 2000); //Scale it to the proper range
  int pitchValue = pitchTemp;
  pitchValue = generatePWM(pitchValue, pitchStart, pitchEnd, 1000, 2000); //Scale it to the proper range
  int yawValue = yawTemp;
  yawValue = generatePWM(yawValue, yawStart, yawEnd, 1000, 2000); //Scale it to the proper range
  int rollValue = rollTemp;
  rollValue = generatePWM(rollValue, rollStart, rollEnd, 1000, 2000); //Scale it to the proper range

  //Allow interrupts again
  interrupts();

  esc1.writeMicroseconds(pitchValue);

  /*
  //Print results
  Serial.print("Throttle Signal: ");
  Serial.print(throttleValue);
  Serial.print(" us");
  Serial.print(" | ");
  Serial.print("Pitch Signal: ");
  Serial.print(pitchValue);
  Serial.print(" us");
  Serial.print(" | ");
  Serial.print("Yaw Signal: ");
  Serial.print(yawValue);
  Serial.print(" us");
  Serial.print(" | ");
  Serial.print("Roll Signal: ");
  Serial.print(rollValue);
  Serial.print(" us");
  Serial.print(" | ");
  Serial.println();
  
  delay(100); //Delay to keep serial monitor
  */

}

void readThrottle() {
  if (digitalRead(throttlePin) == HIGH) {
    throttlePWMStart = micros();
  } else {
    if (throttlePWMStart != 0) {
      int pulseTime = (int)(micros() - throttlePWMStart); 
      if (pulseTime > 800 && pulseTime < 2200) { //Basic filtering
        throttleTemp = pulseTime;
      }
    }
  }
}

void readPitch() {
  if (digitalRead(pitchPin) == HIGH) {
    pitchPWMStart = micros();
  } else {
    if (pitchPWMStart != 0) {
      int pulseTime = (int)(micros() - pitchPWMStart); 
      if (pulseTime > 800 && pulseTime < 2200) { //Basic filtering
        pitchTemp = pulseTime;
      }
    }
  }
}

void readYaw() {
  if (digitalRead(yawPin) == HIGH) {
    yawPWMStart = micros();
  } else {
    if (yawPWMStart != 0) {
      int pulseTime = (int)(micros() - yawPWMStart); 
      if (pulseTime > 800 && pulseTime < 2200) { //Basic filtering
        yawTemp = pulseTime;
      }
    }
  }
}

void readRoll() {
  if (digitalRead(rollPin) == HIGH) {
    rollPWMStart = micros();
  } else {
    if (rollPWMStart != 0) {
      int pulseTime = (int)(micros() - rollPWMStart); 
      if (pulseTime > 800 && pulseTime < 2200) { //Basic filtering
        rollTemp = pulseTime;
      }
    }
  }
}


//Scale the transmitter values to the motor
int generatePWM(int rawValue, int oldRangeStart, int oldRangeEnd, int newRangeStart, int newRangeEnd){
  int result = constrain(map(rawValue, oldRangeStart, oldRangeEnd, newRangeStart, newRangeEnd), newRangeStart, newRangeEnd);
  return result;
}
