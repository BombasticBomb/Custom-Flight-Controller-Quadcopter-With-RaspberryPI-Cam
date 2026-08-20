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
#include "mpu6500.h" //I got fucking scammed so i now gotta use mpu6500 instead of mpu9250!!!

//Flight state variables
bool flight = false;
char flightMode;
float maxFlightSpeed = 0;

//Variables
const int throttlePin = 2; volatile unsigned long throttlePWMStart = 0; volatile int throttleTemp = 1000; 
const int pitchPin = 3; volatile unsigned long pitchPWMStart = 0; volatile int pitchTemp = 1000;
const int yawPin = 4; volatile unsigned long yawPWMStart = 0; volatile int yawTemp = 1000;
const int rollPin = 5; volatile unsigned long rollPWMStart = 0; volatile int rollTemp = 1000;
int minPWM = 1000; int maxPWM = 2000;
int minTilt = -20; int maxTilt = 20; //Tilting of the drone
float currentPitchAngle = 0.0; float currentYawAngle = 0.0; float currentRollAngle = 0.0;
float ax; float ay; float az; float gx; float gy; float gz; float mx; float my; float mz;

//Loop frequency regulation
float loopRate = 500.0; //Loop rate in Hertz (Hz)
const unsigned long refreshInterval = 1000000 / loopRate; // 2000 microseconds
unsigned long previousMicros = 0;

//MPU9250 & BMP280
int imuCSPin = A0;
int bmpCSPin = A1;
bfs::Mpu6500 imu(&SPI, imuCSPin);

//Transmitter Ranges
int throttleStart = 944; int throttleEnd = 1944;
int pitchStart = 1196; int pitchEnd = 1694;
int yawStart = 1248; int yawEnd = 1752;
int rollStart = 1296; int rollEnd = 1800;

//---PID Variables---
//Pitch Angles & Rate Varibales
float pitchAngleKp = 2.0f; float pitchAngleKi = 0.00f; float pitchAngleKd = 0.0f;
float pitchAngleIntegral = 0.0f; float pitchAngleLastError = 0.0f;
float pitchRateKp = 1.0f; float pitchRateKi = 0.00f; float pitchRateKd = 0.0f;
float pitchRateIntegral = 0.0f; float pitchRateLastError = 0.0f;
//Roll Angles & Rate Variables
float rollAngleKp = 2.0f; float rollAngleKi = 0.00f; float rollAngleKd = 0.0f;
float rollAngleIntegral = 0.0f; float rollAngleLastError = 0.0f;
float rollRateKp = 0.75f; float rollRateKi = 0.00f; float rollRateKd = 0.0f;
float rollRateIntegral = 0.0f; float rollRateLastError = 0.0f;
//Yaw Angle 
float yawAngleKp = 0.5f; float yawAngleKi = 0.00f; float yawAngleKd = 0.0f;
float yawAngleIntegral = 0.0f; float yawAngleLastError = 0.0f;
//Storage variables
const float dt = 1.0 / loopRate; int pidPitch = 0; int pidYaw = 0; int pidRoll = 0;
const float pidPWMMin = -450; const float pidPWMMax = 450;

//Sensor fusion variables
float gyroPitch = 0; float gyroYaw = 0; float gyroRoll = 0;
float accelPitch = 0; float accelRoll = 0;
float radToDeg = 57.2957795f; 
float gxBias; float gyBias; float gzBias;
float axBias; float ayBias; 
const int numSamples = 4000; //Bias correcting samples
int successfulSamples = 0;

//Define Motors
Servo esc1; int esc1Pin = 6;
Servo esc2; int esc2Pin = 7;
Servo esc3; int esc3Pin = 8;
Servo esc4; int esc4Pin = 9;
bool motorsEnabled = true;


void setup() {
  Serial.begin(115200);
  SPI.begin();

  //Set the pins as input
  pinMode(throttlePin, INPUT);
  pinMode(pitchPin, INPUT);
  pinMode(yawPin, INPUT);
  pinMode(rollPin, INPUT);
  
  //Set the CS pin on GY-91 to input, as I'm using analog pins as I ran out of digital IO
  pinMode(imuCSPin, OUTPUT);
  digitalWrite(imuCSPin, HIGH);
  pinMode(bmpCSPin, OUTPUT);
  digitalWrite(bmpCSPin, HIGH);

  // Initialize the MPU9250
  if (!imu.Begin()) {
    Serial.println("Error initializing communication with IMU");
    while(1) {} // Halt if sensor not found
  }
  // Configure internal Digital Low Pass Filters (DLPF)
  imu.ConfigAccelRange(bfs::Mpu6500::ACCEL_RANGE_16G);
  imu.ConfigGyroRange(bfs::Mpu6500::GYRO_RANGE_2000DPS);
  imu.ConfigDlpfBandwidth(bfs::Mpu6500::DLPF_BANDWIDTH_184HZ);

  //Using the Arduino PCINT Library, it is a pin change library
  attachPCINT(digitalPinToPCINT(throttlePin), readThrottle, CHANGE); 
  attachPCINT(digitalPinToPCINT(pitchPin), readPitch, CHANGE);
  attachPCINT(digitalPinToPCINT(yawPin), readYaw, CHANGE); 
  attachPCINT(digitalPinToPCINT(rollPin), readRoll, CHANGE); 

  //Attach and Arm ESCs
  esc1.attach(esc1Pin); 
  esc2.attach(esc2Pin); 
  esc3.attach(esc3Pin); 
  esc4.attach(esc4Pin);

  //Zero throttle for stopping
  esc1.writeMicroseconds(minPWM);
  esc2.writeMicroseconds(minPWM);
  esc3.writeMicroseconds(minPWM);
  esc4.writeMicroseconds(minPWM);

  // Calibrate gyro bias 
  while (successfulSamples < numSamples) {
    if (imu.Read()) {
      gxBias += imu.gyro_x_radps();
      gyBias += imu.gyro_y_radps();
      gzBias += imu.gyro_z_radps();

      axBias += imu.accel_x_mps2(); 
      ayBias += imu.accel_y_mps2(); 
      successfulSamples++;
    }
    delayMicroseconds(250);
  }
  gxBias /= numSamples;
  gyBias /= numSamples;
  gzBias /= numSamples;

  axBias /= numSamples;
  ayBias /= numSamples;
   
  delay(2000); //Wait 2 seconds for arming

  // Initialize clock timing anchor right before entering the loop
  previousMicros = micros(); 
}

void loop() {
  unsigned long currentMicros = micros();

  //500Hz loop
  if ((currentMicros - previousMicros) >= refreshInterval){
    
    // Safety check: if we fell behind by more than 5ms, reset anchor to avoid death spiral
    if ((currentMicros - previousMicros) > 5000) {
      previousMicros = currentMicros;
    } else {
      previousMicros += refreshInterval;
    }

    //Set flight mode
    setFlightMode('S');
    

    //Set no interrupt to not corrupt data
    noInterrupts();
    
    //Fetching value from interrupts
    int throttleRC = throttleTemp;
    int pitchRC = pitchTemp;
    int yawRC = yawTemp;
    int rollRC = rollTemp;
  
    //Allow interrupts again
    interrupts();
    
    //Scale it to the proper range
    throttleRC = generatePWM(throttleRC, throttleStart, throttleEnd, minPWM, maxPWM); 
    pitchRC = generatePWM(pitchRC, pitchStart, pitchEnd, minPWM, maxPWM); 
    yawRC = generatePWM(yawRC, yawStart, yawEnd, minPWM, maxPWM); 
    rollRC = generatePWM(rollRC, rollStart, rollEnd, minPWM, maxPWM); 
  
    //Read from MPU9250
    if (imu.Read()){
      ax = imu.accel_x_mps2() - axBias; ay = imu.accel_y_mps2() - ayBias; az = imu.accel_z_mps2();
      gx = imu.gyro_x_radps() - gxBias; gy = imu.gyro_y_radps() - gyBias; gz = imu.gyro_z_radps() - gzBias;
    }

    // Invert az to correct the negative gravity vector
    float corrected_az = -az;

    //Calculate angles from accelerometer
    accelPitch = atan2(ax, sqrt(ay * ay + corrected_az * corrected_az)) * radToDeg;
    accelRoll  = -atan2(ay, corrected_az) * radToDeg;

    // Gyro Pitch rate converted to degrees
    gyroPitch = gy * radToDeg;
    gyroRoll = gx * radToDeg;
    gyroYaw = gz * radToDeg;

    // Initialize angles on the very first run
    if (!flight) {
      currentPitchAngle = accelPitch;
      currentRollAngle = accelRoll;
      currentYawAngle = gyroYaw;
      flight = true;
      currentYawAngle = 0.0f;
    } 
    else {
      //Complementary Filter
      currentPitchAngle = 0.95f * (currentPitchAngle + gyroPitch * dt) + 0.05f * accelPitch;
      currentRollAngle  = 0.95f * (currentRollAngle  + gyroRoll * dt)  + 0.05f * accelRoll;
      currentYawAngle += (gyroYaw * dt);
    }
      
    //Convert receiver signals to degrees
    float targetPitchAngle = constrain(mapF(pitchRC, minPWM, maxPWM, minTilt, maxTilt), minTilt, maxTilt);
    float targetYawAngle   = constrain(mapF(yawRC, minPWM, maxPWM, minTilt, maxTilt), minTilt, maxTilt);
    float targetRollAngle  = constrain(mapF(rollRC, minPWM, maxPWM, minTilt, maxTilt), minTilt, maxTilt);

    //Reset PID if throttle goes too low to avoid integral buildup while on the ground
    if (throttleRC < 1050){
      pitchAngleIntegral = 0; pitchRateIntegral = 0;
      rollAngleIntegral = 0; rollRateIntegral = 0;
      yawAngleIntegral = 0;
      flight = false;
    }

    //Cascaded PID loop
    float targetPitchRate = calculatePID(targetPitchAngle, currentPitchAngle, pitchAngleIntegral, pitchAngleLastError, pitchAngleKp, pitchAngleKi, pitchAngleKd, dt);
    pidPitch = round(calculatePID(targetPitchRate, gyroPitch, pitchRateIntegral, pitchRateLastError, pitchRateKp, pitchRateKi, pitchRateKd, dt));

    float targetRollRate = calculatePID(targetRollAngle, currentRollAngle, rollAngleIntegral, rollAngleLastError, rollAngleKp, rollAngleKi, rollAngleKd, dt);
    pidRoll = round(calculatePID(targetRollRate, gyroRoll, rollRateIntegral, rollRateLastError, rollRateKp, rollRateKi, rollRateKd, dt));

    pidYaw = round(calculatePID(targetYawAngle, currentYawAngle, yawAngleIntegral, yawAngleLastError, yawAngleKp, yawAngleKi, yawAngleKd, dt));
  
    //Send motor pulses
    checkCrash();
    if (motorsEnabled && (flight == true)) {
        mixMotors(throttleRC, pidPitch, pidYaw, pidRoll);
    }
    else {
        esc1.writeMicroseconds(minPWM);
        esc2.writeMicroseconds(minPWM);
        esc3.writeMicroseconds(minPWM);
        esc4.writeMicroseconds(minPWM);
        flight = false;
    }

    /*
    //Print results
    Serial.print("Throttle Signal: ");
    Serial.print(throttleRC);
    Serial.print(" us");
    Serial.print(" | ");
    Serial.print("Pitch Signal: ");
    Serial.print(pitchRC);
    Serial.print(" us");
    Serial.print(" | ");
    Serial.print("Yaw Signal: ");
    Serial.print(yawRC);
    Serial.print(" us");
    Serial.print(" | ");
    Serial.print("Roll Signal: ");
    Serial.print(rollRC);
    Serial.print(" us");
    Serial.print(" | ");
    Serial.println();
    
    delay(100); //Delay to keep serial monitor
    */

    /*
    Serial.print("Pitch: "); Serial.print(currentPitchAngle, 2);
    Serial.print(" | Roll: "); Serial.println(currentRollAngle, 2);
    */
    
  }
  
  
}

//Receiver Main Function
void readPWM(int pin, volatile unsigned long &startTime, volatile int &value) {
  if (digitalRead(pin) == HIGH) {
    startTime = micros();
  } else {
    if (startTime != 0) {
      int pulseTime = micros() - startTime;
      if (pulseTime > 800 && pulseTime < 2200) { //Basic filtering  
        value = pulseTime;
      }
    }
  }
}

//Receiver Channel Functions
void readThrottle() { readPWM(throttlePin, throttlePWMStart, throttleTemp); }
void readPitch()    { readPWM(pitchPin, pitchPWMStart, pitchTemp); }
void readYaw()      { readPWM(yawPin, yawPWMStart, yawTemp); }
void readRoll()     { readPWM(rollPin, rollPWMStart, rollTemp); }



//Scale the transmitter values to the motor
int generatePWM(int rawValue, float oldRangeStart, float oldRangeEnd, float newRangeStart, float newRangeEnd){
  float result = mapF(rawValue, oldRangeStart, oldRangeEnd, newRangeStart, newRangeEnd);
  result = constrain(result, newRangeStart, newRangeEnd);
  return round(result);
}

//Fix yaw once it gets to hover
void mixMotors(int throttleRC, float pid_pitch, float pid_yaw, float pid_roll) {
  //Quad-X matrix (I am going counterclockwise)
  int m1_speed = throttleRC - pid_roll - pid_pitch - pid_yaw; // Front-Right
  int m2_speed = throttleRC - pid_roll + pid_pitch + pid_yaw; // Front-Left
  int m3_speed = throttleRC + pid_roll + pid_pitch - pid_yaw; // Rear-Left
  int m4_speed = throttleRC + pid_roll - pid_pitch + pid_yaw; // Rear-Right
  

  //Constrain
  m1_speed = constrain(m1_speed, minPWM, maxPWM);
  m2_speed = constrain(m2_speed, minPWM, maxPWM);
  m3_speed = constrain(m3_speed, minPWM, maxPWM);
  m4_speed = constrain(m4_speed, minPWM, maxPWM);

  //Send pulses
  esc1.writeMicroseconds(m1_speed);
  esc2.writeMicroseconds(m2_speed);
  esc3.writeMicroseconds(m3_speed); 
  esc4.writeMicroseconds(m4_speed);
}

float calculatePID(float target, float current, float &integral, float &lastError, float kp, float ki, float kd, float dt) {
  if (dt <= 0.0) return 0.0;
  // Calculate error
  float error = target - current;

  // Calculate Integral
  integral += error * dt;
  integral = constrain(integral, pidPWMMin, pidPWMMax);

  // Calculate Derivative
  float derivative = (error - lastError) / dt;
  lastError = error; 

  // Add to make the final controller: P + I + D
  float output = (kp * error) + (ki * integral) + (kd * derivative);
  
  return constrain(output, pidPWMMin, pidPWMMax);
}

float mapF(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


//Set Flight Mode 
void setFlightMode(char mode){
  if(mode == 'N'){
    maxFlightSpeed = 0.7;
  }
  else if(mode == 'C'){
    maxFlightSpeed = 0.6;
  }
  else if (mode == 'S'){
    maxFlightSpeed = 1.0;
  }
}

void checkCrash() {
  if (abs(currentRollAngle) > 70 ||
      abs(currentPitchAngle) > 70 ||
      abs(gyroRoll) > 500 ||
      abs(gyroPitch) > 500) {

    motorsEnabled = false;
  }
}
