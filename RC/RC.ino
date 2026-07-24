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
#include <ServoTimer2.h>
#include "mpu9250.h"
#include <MahonyAHRS.h>

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
bfs::Mpu9250 imu(&SPI, imuCSPin);
Mahony filter;

//Transmitter Ranges
int throttleStart = 944; int throttleEnd = 1944;
int pitchStart = 1196; int pitchEnd = 1694;
int yawStart = 1248; int yawEnd = 1752;
int rollStart = 1296; int rollEnd = 1800;

//PID Variables
float rollSetpoint = 0.0; float rollInput = 0.0; float rollLastError = 0.0; float rollIntegral = 0.0; 
float pitchSetpoint = 0.0; float pitchInput = 0.0; float pitchLastError = 0.0; float pitchIntegral = 0.0; 
float yawSetpoint = 0.0; float yawInput = 0.0; float yawLastError = 0.0; float yawIntegral = 0.0; 
float Kp = 1.5; float Ki = 0.05; float Kd = 0.4; float dt = 1.0 / loopRate; int pidPitch = 0; int pidYaw = 0; int pidRoll = 0;


//Define Motors
ServoTimer2 esc1; int esc1Pin = 6;
ServoTimer2 esc2; int esc2Pin = 7;
ServoTimer2 esc3; int esc3Pin = 8;
ServoTimer2 esc4; int esc4Pin = 9;

void setup() {
  Serial.begin(115200);
  SPI.begin();
  filter.begin(loopRate); // filter to expect 500 measurements per second

  //Set the pins as input
  pinMode(throttlePin, INPUT);
  pinMode(pitchPin, INPUT);
  pinMode(yawPin, INPUT);
  pinMode(rollPin, INPUT);
  
  //Set the CS pin on GY-91 to input, as I'm using analog pins as I ran out of digital IO
  pinMode(imuCSPin, OUTPUT);
  digitalWrite(imuCSPin, HIGH);

  // Initialize the MPU9250
  if (!imu.Begin()) {
    Serial.println("Error initializing communication with IMU");
    while(1) {} // Halt if sensor not found
  }
  // Configure internal Digital Low Pass Filters (DLPF)
  imu.ConfigAccelRange(bfs::Mpu9250::ACCEL_RANGE_8G);
  imu.ConfigGyroRange(bfs::Mpu9250::GYRO_RANGE_500DPS);
  imu.ConfigDlpfBandwidth(bfs::Mpu9250::DLPF_BANDWIDTH_41HZ);

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
  esc1.write(minPWM);
  esc2.write(minPWM);
  esc3.write(minPWM);
  esc4.write(minPWM);
   
  delay(5000); //Wait 5 seconds for arming

  // Initialize clock timing anchor right before entering the loop
  previousMicros = micros(); 
}

void loop() {
  unsigned long currentMicros = micros();

  //500Hz loop
  if ((currentMicros - previousMicros) >= refreshInterval){
    
    // Keep absolute interval accumulation to avoid fractional time drift
    previousMicros += refreshInterval;

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
      ax = imu.accel_x_mps2(); ay = imu.accel_y_mps2(); az = imu.accel_z_mps2();
      gx = imu.gyro_x_radps(); gy = imu.gyro_y_radps(); gz = imu.gyro_z_radps();
      mx = imu.mag_x_ut(); my = imu.mag_y_ut(); mz = imu.mag_z_ut();
    }
    // Update the Mahony filter
    filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);
  
    //Get normalised values for current angles
    currentPitchAngle = filter.getPitch();
    currentYawAngle = filter.getYaw();
    currentRollAngle = filter.getRoll();
      
    //Convert receiver signals to degrees
    float targetPitchAngle = constrain(map(pitchRC, minPWM, maxPWM, minTilt, maxTilt), minTilt, maxTilt);
    float targetYawAngle   = constrain(map(yawRC, minPWM, maxPWM, minTilt, maxTilt), minTilt, maxTilt);
    float targetRollAngle  = constrain(map(rollRC, minPWM, maxPWM, minTilt, maxTilt), minTilt, maxTilt);

    //Reset PID if throttle goes too low to avoid integral buildup while on the ground
    if (throttleRC < 1050){
      pitchIntegral = 0;
      rollIntegral = 0;
      yawIntegral = 0;
    }

    //Calculate PID values for Pitch, Yaw, and Roll
    pidPitch = calculatePID(targetPitchAngle, currentPitchAngle, pitchLastError, pitchIntegral, dt);
    pidYaw = calculatePID(targetYawAngle, currentYawAngle, yawLastError, yawIntegral, dt);
    pidRoll = calculatePID(targetRollAngle, currentRollAngle, rollLastError, rollIntegral, dt);
  
    //Send motor pulses
    mixMotors(throttleRC, pidPitch, pidYaw, pidRoll);

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
int generatePWM(int rawValue, int oldRangeStart, int oldRangeEnd, int newRangeStart, int newRangeEnd){
  int result = constrain(map(rawValue, oldRangeStart, oldRangeEnd, newRangeStart, newRangeEnd), newRangeStart, newRangeEnd);
  return result;
}


void mixMotors(int throttleRC, float pid_pitch, float pid_yaw, float pid_roll) {
  //Quad-X matrix (I am going counterclockwise)
  int m1_speed = throttleRC - pid_roll + pid_pitch - pid_yaw; // Front-Right
  int m2_speed = throttleRC + pid_roll + pid_pitch + pid_yaw; // Front-Left
  int m3_speed = throttleRC + pid_roll - pid_pitch - pid_yaw; // Rear-Left
  int m4_speed = throttleRC - pid_roll - pid_pitch + pid_yaw; // Rear-Right
  

  //Constrain
  m1_speed = constrain(m1_speed, minPWM, maxPWM);
  m2_speed = constrain(m2_speed, minPWM, maxPWM);
  m3_speed = constrain(m3_speed, minPWM, maxPWM);
  m4_speed = constrain(m4_speed, minPWM, maxPWM);

  //Send pulses
  esc1.write(m1_speed);
  esc2.write(m2_speed);
  esc3.write(m3_speed); 
  esc4.write(m4_speed);
}

int calculatePID(float target, float currentAngle, float &lastError, float &integral, float dt) {
  if (dt <= 0.0) return 0;
  // Calculate error
  float error = target - currentAngle;

  // Calculate Integral
  integral += error * dt;
  integral = constrain(integral, -450.0, 450.0);

  // Calculate Derivative
  float derivative = (error - lastError) / dt;
  lastError = error; 

  // Add to make the final controller: P + I + D
  float output = (Kp * error) + (Ki * integral) + (Kd * derivative);
  
  return (int)constrain(output, -450.0, 450.0);
}
