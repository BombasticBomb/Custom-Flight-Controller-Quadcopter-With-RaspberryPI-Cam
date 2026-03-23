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
int hover = 50; //***Assume 50% for hovering, change later***


void setup() {
  //Serial
  Serial.begin(115200);
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
  /*
    -If the stick is at the very bottom: The value will be ~1000.
    -If the stick is halfway up: The value will be ~1500.
    -If the stick is at the very top: The value will be ~2000.
  */
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
      motor1_speed = hover;
      motor2_speed = hover;
      motor3_speed = hover;
      motor4_speed = hover;
      update_speed();
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
