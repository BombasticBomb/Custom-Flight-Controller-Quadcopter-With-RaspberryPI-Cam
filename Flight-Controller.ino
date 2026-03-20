#include <SPI.h>
#include <Wire.h>
#include <MPU6050.h>

//MPU
MPU6050 mpu; //I am using mpu6050 cause I have that with me so I can test with it. After I recieve my mpu9250, I'll update the code to use that. 

bool initialized = false;

// Timing
unsigned long prevTime = 0;
unsigned long lastDisplay = 0;

// Angles
float roll = 0;
float pitch = 0;
float yaw = 0;

// Accel angles
float accel_roll = 0;
float accel_pitch = 0;

//Motor libraries
#include <Servo.h>
#include <IBusBM.h>

//Define 4 motors
Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

//Define bus for radio communication
IBusBM iBus;

//Flight state
bool flight = false;
int motor1_speed = 0;
int motor2_speed = 0;
int motor3_speed = 0;
int motor4_speed = 0;

void setup() {
  Serial.begin(115200);

  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_8G)) { //2000 degrees and 8G
    Serial.println("Sensor not found!");
    delay(500);
  }
  mpu.setDLPFMode(MPU6050_DLPF_4); 

  // Gyro calibration
  mpu.calibrateGyro();
  mpu.setThreshold(0);

  prevTime = millis();

  iBus.begin(Serial);
  
  //Connect wires (pin 3,4,5,6)
  motor1.attach(3);
  motor2.attach(4);
  motor3.attach(5);
  motor4.attach(6);

  //Ground drone
  ground();
  
  //Wait 3 seconds for initialization
  delay(3000);
}

void loop() {
  unsigned long now = millis();
  float dt = (now - prevTime) / 1000.0;
  prevTime = now;

  // Read sensors
  Vector gyro = mpu.readNormalizeGyro();
  Vector accel = mpu.readNormalizeAccel();

  // Compute accel angles
  accel_roll = atan2(accel.YAxis, accel.ZAxis) * 180.0 / M_PI;
  accel_pitch = -atan2(accel.XAxis, sqrt(accel.YAxis * accel.YAxis + accel.ZAxis * accel.ZAxis)) * 180.0 / M_PI;

  // Initialize
  if (!initialized) {
    roll = accel_roll;
    pitch = accel_pitch;
    yaw = 0;
    initialized = true;
  } 
  
  else {
    float alpha = 0.98;

    //sensor fusion
    roll = alpha * (roll + gyro.XAxis * dt) + (1 - alpha) * accel_roll;
    pitch = alpha * (pitch + gyro.YAxis * dt) + (1 - alpha) * accel_pitch;

    //Yaw
    yaw += gyro.ZAxis * dt;
  }

  /*
    -If the stick is at the very bottom: The value will be ~1000.
    -If the stick is halfway up: The value will be ~1500.
    -If the stick is at the very top: The value will be ~2000.
  */
  //I am guessing this information based on the internet, but the truth will unveil when I actually test the reciever and transmitter
  int altitude = iBus.readChannel(2);
  int rotation = iBus.readChannel(3);
  int lr = iBus.readChannel(0);
  int fb = iBus.readChannel(1);

  

  //Up and down
  //=========================================================================
  if(abs(altitude - 1500) < 10){
    if(!flight){
      ground();
    }
    else{
      //This is when drone is stable in the air
      stabilize(roll, pitch, gyro, dt, motor1_speed, motor2_speed, motor3_speed, motor4_speed);
    }
  }
  
  else{
    if(altitude >= 1510){
      motor1_speed = map(altitude, 1510, 2000, 50, 100);
      motor2_speed = map(altitude, 1510, 2000, 50, 100);
      motor3_speed = map(altitude, 1510, 2000, 50, 100);
      motor4_speed = map(altitude, 1510, 2000, 50, 100);
      update_speed();

      //Toggle flight mode
      flight = true;
    }
    if(altitude <= 1490){
      if(flight){
        motor1_speed = map(altitude, 1000, 1490, 0, 50);
        motor2_speed = map(altitude, 1000, 1490, 0, 50);
        motor3_speed = map(altitude, 1000, 1490, 0, 50);
        motor4_speed = map(altitude, 1000, 1490, 0, 50);
        update_speed(); 
      }
    }
    else{
      return;
    }
  }
  //=========================================================================


  //Rotation
  //=========================================================================
  if(rotation > 1500){
    //***20% increase/decrease for rotation
    motor1_speed += 20;
    motor2_speed -= 20;
    motor3_speed += 20;
    motor4_speed -= 20;
    update_speed();
  }
  if(rotation < 1500){
    motor1_speed -= 20;
    motor2_speed += 20;
    motor3_speed -= 20;
    motor4_speed += 20;
    update_speed();
  }
  //=========================================================================

  //Left/Right
  //=========================================================================
  if(lr > 1500){
    //***20% increase/decrease for left/right
    motor1_speed -= 20;
    motor2_speed -= 20;
    motor3_speed += 20;
    motor4_speed += 20;
    update_speed();
  }
  if(lr < 1500){
    motor1_speed += 20;
    motor2_speed += 20;
    motor3_speed -= 20;
    motor4_speed -= 20;
    update_speed();
  }
  //=========================================================================

  //Front/Back
  //=========================================================================
  if(fb > 1500){
    //***20% increase/decrease for front/back
    motor1_speed -= 20;
    motor2_speed += 20;
    motor3_speed += 20;
    motor4_speed -= 20;
    update_speed();
  }
  if(fb < 1500){
    motor1_speed += 20;
    motor2_speed -= 20;
    motor3_speed -= 20;
    motor4_speed += 20;
    update_speed();
  }
  //=========================================================================

  //Check for speed to ground
  if(motor1_speed <= 10 || motor2_speed <= 10 || motor3_speed <= 10 || motor4_speed <= 10){
    ground();
    flight = false;
  }

}

//Stabilizing function
void stabilize(float roll, float pitch, Vector gyro, float dt, int &motor1_speed, int &motor2_speed, int &motor3_speed, int &motor4_speed) {
  //This is a basic stabilize loop to control the drone while in stabilization

  
  //PID constants, tune later after physically building the drones
  float Kp = 1.5;
  float Ki = 0.0;
  float Kd = 0.5;

  //0* for stability
  float target_roll = 0;
  float target_pitch = 0;

  
  float integral_roll = 0;
  float integral_pitch = 0;

  float prev_error_roll = 0;
  float prev_error_pitch = 0;

  float error_roll = target_roll - roll;
  float error_pitch = target_pitch - pitch;

  //Integrate
  integral_roll += error_roll * dt;
  integral_pitch += error_pitch * dt;


  //Derivative
  float d_roll = -gyro.XAxis;
  float d_pitch = -gyro.YAxis;

  //PID = P + I + D
  float roll_output  = Kp * error_roll  + Ki * integral_roll  + Kd * d_roll;
  float pitch_output = Kp * error_pitch + Ki * integral_pitch + Kd * d_pitch;

  //Motor output
  motor1_speed = motor1_speed - roll_output + pitch_output;
  motor2_speed = motor2_speed + roll_output + pitch_output;
  motor3_speed = motor3_speed + roll_output - pitch_output;
  motor4_speed = motor4_speed - roll_output - pitch_output;

  //control it to 100%
  motor1_speed = constrain(motor1_speed, 0, 100);
  motor2_speed = constrain(motor2_speed, 0, 100);
  motor3_speed = constrain(motor3_speed, 0, 100);
  motor4_speed = constrain(motor4_speed, 0, 100);

  //Update motors
  update_speed();
}


//Set speed of the motors
void set_speed(Servo &motor, int throttle){
  int ms = map(throttle, 0, 100, 1000, 2000);
  motor.writeMicroseconds(ms);
  delay(5);
}

//Ground drone
void ground(){
  motor1.writeMicroseconds(1000);
  motor2.writeMicroseconds(1000);
  motor3.writeMicroseconds(1000);
  motor4.writeMicroseconds(1000);
}

void update_speed(){
  set_speed(motor1, motor1_speed);
  set_speed(motor2, motor2_speed);
  set_speed(motor3, motor3_speed);
  set_speed(motor4, motor4_speed);
}
